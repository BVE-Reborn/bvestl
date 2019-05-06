include(vcpkg_common_functions)

vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO BVE-Reborn/eastl-polyalloc
    REF v0.4
    SHA512 c0f1ca694b83f3ad61db0cb721799b77c17117895a9780f20d86502744f2c14f09acfcb8528a0c2186fda78633b6d3c40b0dc03a9bcd375023f2fd9591b2f3ea
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
