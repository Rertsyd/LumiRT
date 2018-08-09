# LumiRT ~ A basic raytracer

## Usages
---

Just open it in Visual Studio 2017 (Windows SDK 10.0.17134.0) and F5 to build'n run

`-> $(SolutionDir)/bin/$(Configuration)/LumiRT.exe $(SolutionDir)/scenes/sceneFile.xml`

.bmp files are created at the project root

I assume that raytracer is used correctly, with correct config, scene, and materials files

There is no error handling, except a global `try/catch` in the `main` function

## Basic Scene file
---

All numerical values are `double` type

Vector properties (positions, directions and colors) are used like this:

`<vec> x y z </vec>`

```
<xml>
<camera>
	<position> x y z </position>
	<look_at> laX laY laZ </look_at>
</camera>
<scene>
	<objects>
		...
	</objects>
	<lights>
		...
	</lights>
</scene>
</xml>
```

### Objects

Supported objects are `Sphere` and `Plane`

```
<sphere>
	<position> x y z </position>
	<radius> r </radius>
</sphere>
```

```
<plane>
	<position> x y z </position>
	<normal> nX nY nZ </normal>
	<!-- optionnal tag : -->
	<rotation> rX rY rZ </rotation>
</plane>
```

Optionnal `rotation` property expressed in degrees.

Both objects need an additional tag : `<material> ... </material>`, 
with as value the name of one of the defined materials (see `Materials` part)

### Lights

Supported lights are `Point` and `Directional`

```
<point>
	<position> x y z </position>
	<color> r g b </color>
</point>
```

```
<directional>
	<direction> x y z </direction>
	<color> r g b </color>
</directional>
```

## Materials
---

Path to materials file is defined in config.xml

By default : `./assets/materials.xml`

```
<xml>
<materials>
	...
</materials>
</xml>
```

Supported material types are `phong`, `reflection`, and `refraction`

All *kvalues* (e.g. `kdiffuse`) are defined between 0 and 1, both inclusive

The name of material is defined by the tag (e.g. `red`)

### Phong
```
<red>
	<type> phong </type>
	<albedo> r g b </albedo>
	<kdiffuse> kd </kdiffuse>
	<kspecular> ks </kspecular>
	<ks_exp> kse </ks_exp>
</red>
```

- `albedo` : color of the material. Common to `phong` and `refraction` types.
- `kdiffuse` : amount of light returned by the object.
- `kspecular` : amount of brightness.
- `ks_exp` : adjust the highlight intensity.

### Reflection
```
<mirror>
	<type> reflection </type>
	<kreflection> krfl </kreflection>
</mirror>
```

- `kreflection` : amount of light reflect by the object.

### Refraction
```
<glass>
	<type> refraction </type>
	<albedo> r g b </albedo>
	<kreflection> krfl </kreflection>
	<krefraction> krfr </krefraction>
	<transparency> t </transparency>
</glass>
```

- `krefraction` : describes the behavior of light in the material. This value is higher than 1 (Water = 1.333, Glass = 1.52, Diamond = 2.42)
- `transparency` : value between opaque (0) to completely transparent (1)
