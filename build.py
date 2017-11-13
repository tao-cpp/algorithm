from conan.packager import ConanMultiPackager

if __name__ == "__main__":
    builder = ConanMultiPackager(username="fpelliccioni", channel="stable",
                                 remotes="https://api.bintray.com/conan/tao-cpp/tao-cpp"
                                 )

    # builder.add_common_builds(shared_option_name="algorithm:shared")
    builder.add_common_builds()

    filtered_builds = []
    for settings, options, env_vars, build_requires in builder.builds:
        # if settings["build_type"] == "Release" \
        #         and not options["algorithm:shared"] \
        #         and (not "compiler.runtime" in settings or not settings["compiler.runtime"] == "MT"):
        filtered_builds.append([settings, options, env_vars, build_requires])

    builder.builds = filtered_builds
    builder.run()
