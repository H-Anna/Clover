# Clover v0.1.0 - A guide to creating a mascot
This is a haphazardly-made guide to creating your own Clover mascot. I've done my best to make it understandable, although sometimes I may use SSP terminology instead of plain language without noticing (eg. using 'mascot' and 'ghost' interchangeably). Feel free to contact me if there's something you don't understand.

## The data folder
The "data" folder contains all of the files the mascot uses. The JSON files specify how the mascot will work. Their contents are read and stored on app startup and remain in memory until the app quits. If you're not familiar with this format, [follow this link to learn about it.](https://www.w3schools.com/js/js_json_intro.asp) This means that distributing your mascot is as easy as creating a zip archive of its data folder.

> Please read the below subsections carefully, as they contain important information when it comes to
> structuring and writing Clover's JSON files. In the future, I'd like to write GUI applications to save time
> for developers and make it simpler to create ghosts for those who don't know how to write code.

The files are generally structured like this:

    {
    	"type": "anchor",
    	"content":
    	[
	    	//...
    	]
    }

The value of `type` will determine how the file is read. `content` contains data relevant to how the mascot functions. Some files may have `{braces}` instead of `[brackets]` after `content` - braces denote objects, brackets denote arrays. Current types in use: `surface, balloon, talk, keytalk, anchor, pool, sound`.

> Detailed description of each file's structure follows. While reading, please refer to the
> data folder for examples. Mandatory fields are marked with **!**. Along with JSON files,
> the files `variables.ini` and `stylesheet.qss` will also be described.

## surfaces.json
This file describes the graphics objects the mascot will use, called **surfaces.** A surface is a single image or multiple images layered dinamically on top of one another at runtime. When the mascot "enters" a surface, a major change in graphics is supposed to occur, such as the character's pose changing. For semantic purposes, image files are recommended to be the same size each.
In this file, a `layercount` is also specified, although this isn't mandatory and currently does nothing.
Contents are specified as an **array of objects.**

- **!** `id`: The ID of the surface, an integer >= 0. Each ID should be unique.
- **!** `elements`: An **array** of strings that are relative paths to image files. Entering the surface will cause these graphics to be displayed. These graphics will be treated as separate layers. You may also specify an empty layer with an empty string. The graphics are displayed "bottom-up," which means that the first element of the array will be the bottom layer and the last will be the top. Clover has been tested with .png files only, but should work with .jpg, .jpeg and possibly .bmp files as well.
- `animations`: **Array of objects,** see below.
- `hotspots`: **Array of objects,** see below.

**Animations** (also called intervals) may be specified - commonly these are still images that change on a timer, or a small change in the graphic that can be called manually. Each surface can only use its own animations, and multiple animations may be active at once. When a new surface is entered, all animations are cleared. Animations are optional to specify, but each of their fields are mandatory.

- **!** `id`: The ID of the animation, an integer >= 0. Each ID should be unique *within a surface,* but they can repeat across surfaces. For example, surface 10 may not have two animations whose IDs are both 0, but surface 10 and surface 11 may each have one animation with ID 0.
- `name`: Animations can be named (string value) for easy access, but this is not required.
- **!** `frequency`: String value that defines how the animation is played. Case sensitive. Possible values:
	- `"Never"`: This animation has to be called manually.
	- `"Always"`: This animation starts when the mascot enters the surface and loops (when it reaches the last frame, it will continue to play from the first frame).
	- `"Loop"`: This animation has to be called manually and loops.
- **!** `layer`: Which layer to perform the animation on.
- **!** `frames`: **Array of objects,** see below. Order is important.

**Frames** are the individual graphics that make up an animation.

- **!** `image`: The relative path to the image file to be displayed. String.
- **!** `drawmethod`: Determines how the frame is displayed. Case sensitive. Possible values:
	- `"Overlay"`: Overlay the image on top of all displayed graphics.
	- `"Insert"`: Insert image on specified layer. Pushes all above layers up one index. In the future this may cause issues.
	- `"Replace"`: Replace image on specified layer.
	- `"Base"` and `"Clip"` can be specified, but do nothing and may cause bugs.
- **!** `ms`: How many milliseconds to display the next frame. Specifying 0 causes the animation to stop. It is also recommended when your animation is a single frame long and is not supposed to expire, such as the lion's perked ears.

**Hotspots** are areas the user can mouse over which send specific signals when certain actions are taken, such as the hotspot being clicked. These are also optional.

- **!** `name`: The name of the hotspot. String.
- **!** `area`: An array of 4 integer values that define the bounding rectangle of the hotspot. These are the top left X, top left Y, bottom right X and bottom right Y coordinates, respectively. These are calculated on the bottom layer graphic of a surface.
- **!** `cursor`: String value of [Qt::CursorShape.](https://doc.qt.io/qt-5/qt.html#CursorShape-enum) Specify without the `Qt::` part. Case sensitive.
- `variables`: **Array of objects.** You can create a variable whose value increases when certain actions are performed on the hotspot.
	- **!** `name`: String, the name of the variable. This should also be specified in [variables.ini.](#variables.ini)
	- **!** `type`: Determines the type of interaction that causes the variable to increase. String. Case sensitive. Possible values: `DoubleClick`, `MouseClick` and `MouseWheel`.

## balloons.json
This file describes the graphics objects the mascot's speech **balloons** will use. Whenever the mascot displays text, this text is displayed in a box-shaped area over an image.
Contents are specified as an **array of objects.**

- **!** `id`: The ID of the balloon, an integer >= 0. 
- **!** `image`: The relative path to the image. String.
- **!** `textarea`: An array of 4 integers that define the bounding rectangle of the text display area. These are the top left X, top left Y, bottom right X and bottom right Y coordinates, respectively. These coordinates are in relation to the image.

## talks.json
This file lists strings called **talks.** Talks contain plain text, HTML tags and **Clover tags,** and the combinations of these define the actions of a mascot. Upon pressing the T key, Clover picks a talk from this file and parses it. Plaintext is displayed, HTML tags are used to style plaintext, and Clover tags perform various functions, such as clearing text from the balloon, changing text printing speed etc.

> Clover is compatible with [Qt's HTML 4 subset,](https://doc.qt.io/qt-5/richtext-html-subset.html) which means not all HTML tags may work.
> Clover is also compatible with CSS stylesheet specification - more on that in the [Text stylesheet](#stylesheet.qss) section.

Contents are specified as an **array of string values.**
JSON's string values are delimited by `"quotation marks"`. When using quotation marks, **you must replace each `"` character with `&quot` to avoid errors.** Clover will replace `&quot` with `"` when displaying text. Other special characters are not affected.
|Correct                                          |Incorrect                                |
|-------------------------------------------------|-----------------------------------------|
|`"<a href=&quothttps://google.com&quot>Link</a>"`|`"<a href="https://google.com">Link</a>"`|
|`"I said &quotI'll be fine&quot and left."`      |`"I said "I'll be fine" and left."`      |
Clover tags are formatted as `<!tag[param]>`. `tag` defines a function, while `param` is a parameter the function takes, though not all tags require one.
> Make sure you don't mix up HTML tags and Clover tags.

Below is a list of Clover tags and their functions. `INT` denotes an integer value, `STRING` denotes a string value, and `VAR` means the value may either be a string or an integer.

|Tag|Parameter|Function
|--|--|--
|`clr`|-|Clears the balloon in focus.
|`hide`|-|Hides the character in focus.
|`show`|-|Shows the character in focus.
|`wait`|`INT`|Pauses talk execution for `INT` milliseconds.
|`timeout`|`INT`|Sets the balloon timeout to `INT` milliseconds. Upon timeout, the balloon expires and disappears. The default value is `20000`. This value resets when the balloon expires.
|`speed` | `INT` |Sets text printing "speed" to `INT` milliseconds. This is actually a delay, which means that higher values will cause text to print slower. The default value is `50`. This value resets when the balloon expires.
|`p`|`INT`|Changes scope. `INT` is the ID of the mascot character. By default, the first character is `0`. This is used to switch between characters that talk to each other.
|`b`|`INT`|Changes the balloon in scope. `INT` is the ID of the balloon surface specified in [balloons.json.](#balloons.json) This clears the balloon.
|`s`|`INT`|Changes the surface for the mascot in scope. `INT` is the ID of the surface specified in [surfaces.json.](#surfaces.json)
|`i`|`INT` or `STRING`|Applies the animation for the mascot in scope. `INT` is the ID of the animation specified for the surface in [surfaces.json.](#surfaces.json) You may also use the name of the animation as the parameter, if it has been specified.
|`get`|`STRING`|Displays the value of the variable named `STRING`. See variables.ini for named variables. Additionally, you may write `<!get[TIME]>` to print the current time.
|`set`|`STRING, VAR`|Sets the value of the variable named `STRING` to `VAR`.
|`play`|`STRING`, `INT`|Plays a sound file named `STRING` defined in [sounds.json.](#sounds.json) You may optionally provide `INT` to tell Clover to loop the sound file `INT` times.
|`stop`|-|Stops currently playing sound.
|`pool`|`STRING`|Pulls a string from a pool names `STRING`. See [pools.json](#pools.json) for more information.

In addition to Clover tags, the HTML tag `<a>` can be used with special **schemes.** In code, a URL specified with this HTML tag will be converted into Qt's QUrl object, allowing for certain parts of the URL to be queried. [Here is an example of a QUrl URL string's structure.](https://doc.qt.io/qt-5/qurl.html#setAuthority) A common scheme is `https`, which refers to a file on the internet. With Clover, you may specify `anchor` or `key` as schemes to create links that, when clicked, cause Clover to parse a talk defined in [anchors.json or keytalk.json,](#keytalk.json-and-anchors.json) respectively.
|Scheme  |Example                                             |
|--------|----------------------------------------------------|
|`anchor`|`<a href=&quotanchor:likemice&quot>I love mice!</a>`|
|`key`   |`<a href=&quotkey:MENU&quot>Menu</a>`               |

## keytalk.json and anchors.json
At this time, these files are similar in function. You may specify a key, or **anchor**, which is a unique string that can be used to refer to a talk. Each anchor has only one talk associated with it.
Contents are specified as an **object containing key-value pairs, and the values must be strings.** Otherwise, these files have no set structure. You may nest and recurse anchors.

## pools.json
In this file, you may specify collections of string called **pools.** Using `<!pool[poolname]>` will specify a pool in the talk. Before parsing, Clover will replace this piece of the talk with a string picked randomly from the pool named `poolname`. This will cause the talk to display differently each time (though repetitions are allowed).
Contents are specified as an **object containing key-array pairs, whose arrays contain string values.** Otherwise, this file has no set structure.
> You may nest pools, but recursing is not recommended, as it may hang Clover.

## sounds.json
In this file, you can specify sound files that Clover can play using the `<!play[soundname]>` tag. MP3 files are confirmed to be supported.
>This can't be used to play sound files from major platforms such as YouTube or Spotify, as it requires direct access to a sound file, such as a URL that ends with `.mp3`.

Contents are specified as an **array of objects.**

- **!** `name`: String that refers to the sound file.
- **!** `type`: String. Specify `file` if it is a file on your computer, or `url` if it is a file on the internet.
- **!** `location`: String. Relative path to the file, or a URL.

## variables.ini
This is a collection of variables Clover handles. When starting, Clover will read and store its contents. When quitting, Clover will overwrite this file with its stored variables' values.

## stylesheet.qss
CSS stylesheets can be applied to Qt Widgets. This file specifically contains a stylesheet that applies a default style to the mascot's balloons' text box. HTML tags written in talks take precedence over the style specifications contained here. [You may read about CSS more in detail here.](https://www.w3schools.com/css/css_intro.asp) As with HTML tags in talks, this stylesheet is restricted to [Qt's HTML subset.](https://doc.qt.io/qt-5/richtext-html-subset.html)
The file must look like this:

    QTextBrowser {
    	//CSS code goes here
    }

In this specific file you can also see the following:

    QTextBrowser#myballoon {
    	color: #8B4513;
    }

You can specify multiple stylesheets. The `QTextBrowser` stylesheet will be applied to every balloon within this mascot. The `QTextBrowser#myballoon` stylesheet will only be applied to QTextBrowser objects (the type of text box Clover uses) named `myballoon`, as Qt allows for naming objects programmatically. The `QTextBrowser#myballoon` stylesheet takes precedence over the `QTextBrowser` stylesheet.
> In the future, this would mean specifying in [balloons.json](#balloons.json) a stylesheet name for
> the balloon being used, and Clover applying the appropriate stylesheet to its text box.
> You may ignore it for now, as at this point, both `QTextBrowser` and
> `QTextBrowser#myballoon` perform the same function.
