# plaits.gdextension

An embedding of the venerable [Plaits](https://web.archive.org/web/20211128142523/https://mutable-instruments.net/modules/plaits/) for [Godot](https://godotengine.org/) with the GDExtension system.

## Usage

1. clone this repo into your project, ideally under an extensions/plaits directory.
2. cd into the directory and run `git submodule update --init`
3. Run `scons` ([see here](https://docs.godotengine.org/en/latest/engine_details/development/compiling/introduction_to_the_buildsystem.html) for more info)
4. `cp extensions/plaits/plaits.gdextension bin/plaits.gdextension` (you may need to tweak the values)
5. In your project, create an AudioStreamPlayer node, then set it's stream to the PlaitsStream

If you have issues / questions / requests, open an issue!
