include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO BVE-Reborn/eastl-polyalloc
    REF v0.5
    SHA512 6419e36e08f9f59bb0dc4cdcda9d1119a0fd8f477272a1d5c84c5207ce81807510dbc65d204afa45257075218fb0d673c360fe79896dd98fc90ceccd825f6497
    HEAD_REF master
)

vcpkg_configure_cmake(
    SOURCE_PATH ${SOURCE_PATH}
    PREFER_NINJA
)

vcpkg_install_cmake()

vcpkg_fixup_cmake_targets()

file(REMOVE_RECURSE ${CURRENT_PACKAGES_DIR}/debug)

# Handle copyright
file(INSTALL ${SOURCE_PATH}/LICENSE DESTINATION ${CURRENT_PACKAGES_DIR}/share/eastl-polyalloc RENAME copyright)
