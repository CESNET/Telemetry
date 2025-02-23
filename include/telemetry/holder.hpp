/**
 * @file
 * @author Lukas Hutak <hutak@cesnet.cz>
 * @brief Holder of telemetry nodes.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#pragma once

#include "node.hpp"

#include <memory>
#include <vector>

namespace telemetry {

/**
 * @brief Holder of telemetry nodes.
 *
 * The class provides auxiliary functions for holding telemetry files and directories.
 * Application components should use this class to hold all their telemetry nodes.
 *
 * In addition, it can be used to collectively disable callbacks for all held files.
 * This is useful when one or more referenced objects (in the callbacks) should no longer
 * be accessible, e.g. because they will be destroyed soon.
 */
class Holder {
public:
	Holder() = default;
	/**
	 * @brief Destructor of the holder.
	 *
	 * Callbacks of all held files are disabled during destruction. Keep on mind that files
	 * might still exist if someone holds their references.
	 */
	virtual ~Holder();

	Holder(const Holder& other) = delete;
	Holder& operator=(const Holder& other) = delete;
	/**
	 * @brief Move constructor
	 * @param other Other holder
	 */
	Holder(Holder&& other) = default;

	/**
	 * @brief Move assignment
	 * @param other Other holder
	 * @return Reference to this holder
	 */
	Holder& operator=(Holder&& other) = default;

	/**
	 * @brief Add a telemetry node.
	 * @param node Node to add
	 */
	void add(const std::shared_ptr<Node>& node);

	/** @brief Disable callbacks of all held files. */
	void disableFiles();

private:
	std::vector<std::shared_ptr<Node>> m_entries;
};

} // namespace telemetry
