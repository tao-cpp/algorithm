import os
from conan.packager import ConanMultiPackager
from ci_utils import get_builder

if __name__ == "__main__":
    # builder = ConanMultiPackager(username="fpelliccioni", channel="stable",
    #                              remotes="https://api.bintray.com/conan/tao-cpp/tao"
    #                              )

    builder, name = get_builder(os.path.dirname(os.path.abspath(__file__)))
    builder.add_common_builds()

    filtered_builds = []
    for settings, options, env_vars, build_requires in builder.builds:
        if settings["build_type"] == "Release":
            filtered_builds.append([settings, options, env_vars, build_requires])

    builder.builds = filtered_builds
    builder.run()
