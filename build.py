import os
from conan.packager import ConanMultiPackager
from ci_utils import get_builder

if __name__ == "__main__":
    builder, name = get_builder(os.path.dirname(os.path.abspath(__file__)))
    builder.add_common_builds()

    filtered_builds = []
    for settings, options, env_vars, build_requires, reference in builder.items:
        if settings["build_type"] == "Release":
            options["%s:tests" % name] = True
            filtered_builds.append([settings, options, env_vars, build_requires, reference])

    builder.builds = filtered_builds
    builder.run()
