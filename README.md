# About

Iteration II is a time travelling puzzle game. You are contacted by an unknown person from the future who tasks you with stopping a nuclear meltdown. Complex situations quickly arise as you find plenty of levers, doors and pressure-plates to interact with, as well as past versions of yourself!

# Compatible Platforms

Although designed to be multi-platform, so far this game has been compiled only on Windows 7 and OS X 10.9.1 (Mavericks).

# Compiling

* Requires SFML
* Should compile under either GCC or Clang
* Remember to uncomment the target OS at the top of Defs.hpp

# Creating Custom Levels

## Introduction

The levels are actually split into two different types: levels and scenes. Levels are the actual gameplay areas, while scenes are the screens of text that convey the story.

## Outline

The outline file, stored at `content\outline.txt`, stores the order of levels and scenes. It is like the contents page of a book, going from top to bottom. Each line must be one of the three following examples:

* `Title: builtin`
* `Scene: <filename>`
* `Level: <filename>`

Where <filename> represents the name of the relevant scene or level file, e.g. `some_level.txt`. The `Title: builtin` simply goes to the game's built in title screen. This allows you to leave out the title screen entirely, or use it at a later date, even repeatedly.

## Scenes

All scene files are stored in `content\scenes\`. They consist simply of lines of text. In the game, each line is displayed one at a time with a small delay between each.

## Levels

All level files are stored in `content\levels\`. Their format is as follows:

* First line: width of level
* Second line: height of level
* Next X amount of lines (where X is the height of the level as defined above): the level map
* (optional) All subsequent lines: parameters and links

### Level Map

The level map is where the initial layout of the level is represented with ASCII. It allows for easily and visually designing levels. The key is as follows:

* Non-walkable
	* `#`: Wall (the specific wall graphic is generated automatically when the game is played)
	* `<space>`: Invisible wall
	* `d`: Door (can be opened manually)
	* `D`: Door (can only be opened via links)
	* `W`: Window (purely cosmetic)
* Walkable
	* `.`: Floor
	* Mechanics
		* `l`: Lever (initial state is off)
		* `L`: Lever (initial state is on)
		* `_`: Pressure plate
		* `=`: Motion alarm
* Implemented but no functionality
	* `r`: Weak radiation
	* `R`: Strong radiation

### Parameters

The following parameters exist:

* `Title: <text>`: The title for the level
* `Subtitle1: <text>`: First line of the subtitle
* `Subtitle2: <text>`: Second line of the subtitle
* `Subtitle3: <text>`: Third line of the subtitle
* `Timelimit: <number>`: How many actions can be performed before the level ends
* `Critical: <number>`: How many actions can be performed before the meltdown goes critical

### Links

Links allow mechanics and doors to be connected together. They connect one object to one other object. This means that you can, for example, link a lever to a door. The lever will then operate opening and closing that door. Links are defined in the following format:

```
Link: <object_from> <link_type> <object_to>
```

Each object must refer to an object in the above level map. References are made by using the object's name, followed by a hash, and the index of that object. The following object names exist:

* `Lever`
* `Plate`
* `Alarm`
* `Door`

The object index is defined by that specific type of object's order in the level map, starting from the top left, reading line by line. For example, if a level contained just one door and one lever, they would be referred to as `Door#1` and `Lever#1`. If, however, a level contained two levers, the one you counter first by reading line by line would be `Lever#1`, and the other would be `Lever#2`.

There are two possible link types:

* `=>`: equal link
* `~>`: inverse link

As an example: a pressure plate connected to a door with an equal link will open the door when it is pressed. If an inverse link were used, the door would be closed when pressed.

Here are some examples of links:

```
Link: Lever#1 => Door#2
Link: Plate#3 ~> Door#1
Link: Alarm#8 => Door#5
```

Objects other than doors can be put on the receiving end of the link, but currently that has no real use.