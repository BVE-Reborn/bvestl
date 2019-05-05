include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO BVE-Reborn/eastl-polyalloc
    REF v0.2.2
    SHA512 7d5a5003a7ebd5b11384aa6ddc630eb37eb6fba7e9c67d98073d4c57f5af069bc963491523972a70a3f5c1c20244a35aa51dd687e550b21f78350fa02f043362
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
