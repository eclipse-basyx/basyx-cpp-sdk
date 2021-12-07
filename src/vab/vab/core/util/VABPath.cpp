/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#include <BaSyx/vab/core/util/VABPath.h>

#include <algorithm>
#include <sstream>


namespace basyx {
namespace vab {
namespace core {


const std::string VABPath::emptyElement{ "" };
const std::string VABPath::operationsString{ "operations" };
const char VABPath::delimiter{ '/' };


VABPath::VABPath(const std::string & path) :
	isValid(false),
	isOperation(false)
{

	auto start = path.begin();
	auto end = path.begin();

	while (start != path.end() && end != path.end())
	{
		// Find an occurrence of the path-delimiter and construct an element
		end = std::find(start, path.end(), delimiter);
		if (start != end)
			elements.emplace_back(start, end);

		// The next cycle should start at the position after the delimiter
		if (end != path.end())
			start = ++end;

		// Add an empty element if found double slashes
		auto end_second = std::find(end, path.end(), delimiter);
		if (end_second == end && end_second != path.end())
		{
			elements.push_back(this->emptyElement);
		}
	}

	// check if path is an operation
	if (elements.size() && elements.back().compare(this->operationsString) == 0)
		isOperation = true;

	isValid = true;
}

VABPath::VABPath(const char path[]) : 
  VABPath(std::string(path))
{
}

VABPath::VABPath(const std::vector<std::string> & elements) :
	elements(elements),
	isOperation(false),
	isValid(false)
{
	// check if path is an operation
	if (elements.size() && elements.back().find(this->operationsString) != std::string::npos)
		this->isOperation = true;

	isValid = true;
}

const std::string VABPath::getLastElement() const {
	if (elements.size())
		return this->elements.back();

	return VABPath::emptyElement;
}

const std::vector<std::string> & VABPath::getElements() const
{
	return this->elements;
}

const VABPath VABPath::getParentPath() const
{
	if (this->elements.empty())
		return VABPath("");

	auto begin = this->elements.cbegin();
	// parent path must be the path without the last element
	auto end = this->elements.cend() - 1;
	std::vector<std::string> subElements(begin, end);

	return VABPath(subElements);
}

void VABPath::removePrefix(const std::string & prefix)
{
	// if no elements present or if the first element and the prefix does not match
	// nothing should be removed
	if (!elements.size() || elements.front().compare(0, prefix.size(), prefix) != 0)
		return;

	// remove the prefix
	auto prefix_position = elements.front().find(prefix);
	elements.front().erase(prefix_position);

	// if first element is empty now, delete it
	if (elements.front().size() == 0)
		elements.erase(this->elements.begin());

	// if second element is empty. also delete
	if (elements.front().size() == 0)
		elements.erase(this->elements.begin());
}

void VABPath::append(const VABPath & path)
{
	this->append(path.toString());
}

void VABPath::append(const std::string & path)
{
	// construct new path 
	VABPath appending_path = VABPath(path);

	// if second path is operation, this one is operation
	this->isOperation = appending_path.isOperationPath();
	// paths are only valid if both paths are valid
	this->isValid &= appending_path.isValidPath();

	// add an empty element to mark that this one is entry-path
	this->elements.push_back(this->emptyElement);

	// add the new elements
	auto new_elements = appending_path.getElements();
	this->elements.insert(this->elements.end(), new_elements.begin(), new_elements.end());
}

std::string VABPath::getAddressEntry()
{
	// get the position where the entry path ends
	auto end_position = this->getEntryEndIterator();

	// construct a new path without the entry
	VABPath entry(std::vector<std::string>(this->elements.begin(), end_position));
	return entry.toString();
}

VABPath VABPath::getAddressEntryPath()
{
	return VABPath(this->getAddressEntry());
}

void VABPath::removeEntry()
{
	// get the position where the entry path ends
	auto end_position = this->getEntryEndIterator();

	this->elements.erase(this->elements.begin(), end_position);

	// if first element is empty -> remove
	if (this->elements.size() && this->elements.front().compare(this->emptyElement) == 0)
		elements.erase(this->elements.begin());
}

std::string VABPath::toString() const {
	if (!this->elements.size())
		return "";

	std::string str;

	//for each element there is a delimiter in string
	for (const auto & element : elements)
		str += element + delimiter;

	// return string without last delimiter
	return std::string(str.cbegin(), str.cend() - 1);
}

std::string VABPath::toStringWithoutPrefix(const std::string& prefix) const
{
	VABPath path(this->elements);
	path.removePrefix(prefix);
	return path.toString();
}

std::string VABPath::toStringWithoutEntry() const
{
	VABPath entryless(this->elements);
	entryless.removeEntry();
	return entryless.toString();
}

VABPath VABPath::operator+ (VABPath const & other)
{
	VABPath new_path(this->toString());
	new_path.append(other);
	return new_path;
}

VABPath::operator std::string() const
{
	return this->toString();
}

const bool VABPath::isValidPath() const
{
	return this->isValid;
}

const bool VABPath::isOperationPath() const
{
	return this->isOperation;
}

const bool VABPath::isEmpty() const
{
	if (!this->elements.empty())
		return this->elements.front().empty();
	return true;
}

std::vector<std::string>::iterator VABPath::getEntryEndIterator()
{
	// Find two occurences of an empty element
	auto first_doubled_slash = std::find(this->elements.begin(), this->elements.end(), this->emptyElement);
	if (first_doubled_slash == this->elements.end())
		return this->elements.end();

	auto second_doubled_slash = std::find(++first_doubled_slash, this->elements.end(), this->emptyElement);
	if (second_doubled_slash == this->elements.end())
		return this->elements.end();

	return second_doubled_slash;
}


}
}
}
