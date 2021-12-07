/*******************************************************************************
 * Copyright (C) 2021 the Eclipse BaSyx Authors
 * 
 * This program and the accompanying materials are made
 * available under the terms of the Eclipse Public License 2.0
 * which is available at https://www.eclipse.org/legal/epl-2.0/
 * 
 * SPDX-License-Identifier: EPL-2.0
 ******************************************************************************/

#ifndef VAB_CORE_UTIL_VABPATH_H
#define VAB_CORE_UTIL_VABPATH_H

#include <memory>
#include <string>
#include <vector>

namespace basyx {
namespace vab {
namespace core {

class VABPath {
private:
  static const char delimiter;
  static const std::string emptyElement;
  static const std::string operationsString;

  std::vector<std::string> elements;

  bool isValid;
  bool isOperation;

  std::unique_ptr<VABPath> entry;
  std::unique_ptr<VABPath> tail;

public:
  /**
      * Constructs a VABPath object.
      * Each element in the path is appended to the elements vector.
      * If path is separated by "//", an empty element is added to elements.
      * I.E.: basyx://127.0.0.1:6998/somepath results in a vector looking like:
      * ["basyx:", "", "127.0.0.1:6998", "somepath"]
      */
  VABPath(const std::string& path);

  /**
  * Constructor for character array. Same functionality as String constructor.
  */
  VABPath(const char path[]);

  /**
      * Constructs a VABPath object.
      * Just copies the elements vector.
      */
  VABPath(const std::vector<std::string>& elements);

  /**
      * The last element of the path is returned.
      * I.e.: For "basyx://127.0.0.1:6998/somepath", the result will be
      * "somepath"
      */
  const std::string getLastElement() const;

  /**
      * Get a vector of the path-elements.
      * I.e.: For the path "basyx://127.0.0.1:6998/somepath" the following vector
      * will be returned:
      * ["basyx:", "", "127.0.0.1:6998", "somepath"]
      */
  const std::vector<std::string>& getElements() const;

  /**
      * Constructs a new VABPath object, with just the parent-path contained.
      * I.e.: "basyx://127.0.0.1:6998/somepaths"
      * will result in "basyx://127.0.0.1:6998"
      */
  const VABPath getParentPath() const;

  /**
      * Removes the given prefix from the path, if existing.
      */
  void removePrefix(const std::string& prefix);

  /**
      * Appends the given path to the existing path.
      */
  void append(const std::string& path);

  /**
      * Appends the given path to the existing path.
      */
  void append(const VABPath& path);

  /**
      * Constructs a new VABPath object, with just the parent-path contained.
      * I.e.: "basyx://127.0.0.1:6998/somepath//https://localhost/test/operations"
      * will result in "basyx://127.0.0.1:6998/somepath"
      */
  VABPath getAddressEntryPath();

  /**
      * As the getAddressEntryPath() method, but returns the appropriate String.
      */
  std::string getAddressEntry();

  /**
      * Removes the address entry if present.
      */
  void removeEntry();

  /**
      * This method generates the path as string.
      */
  std::string toString() const;

  /**
      * Returns the path as string without the given prefix.
      * Does not affect the path itself.
      */
  std::string toStringWithoutPrefix(const std::string& prefix) const;

  /**
      * Returns the path without the address-entry.
      */
  std::string toStringWithoutEntry() const;

  /**
      * Addition of two pathes, same functionality as append but returns a new path object.
      */
  VABPath operator+(VABPath const& other);

  /**
      * Operator for implicit cast to std::string.
      */
  operator std::string() const;

  const bool isValidPath() const;
  const bool isOperationPath() const;
  const bool isEmpty() const;

private:
  std::vector<std::string>::iterator getEntryEndIterator();
};


}
}
};


#endif /* VAB_CORE_UTIL_VABPATH_H */
