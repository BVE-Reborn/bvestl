include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO BVE-Reborn/eastl-polyalloc
    REF v0.3.1
    SHA512 75f11b1e7818419ec136da6fd141ce3c022288fd33268b83ac67c0b1270f54dc8df36cb5ad28eaa7ff93c3ce552e19fb6d58039d1ee10535f00d5e73230b7026
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
