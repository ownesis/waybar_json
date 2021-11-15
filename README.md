# Waybar JSON-format generator

C library for generate a JSON-format for the `return-type` `"json"` in waybar conf file.

> in `waybar-custom(5)` manual page.
```man
RETURN-TYPE
       When return-type is set to json, Waybar expects the exec-script  to output its data in JSON format. This
       should look like this:

           {"text": "$text", "tooltip": "$tooltip", "class": "$class", "percentage": $percentage }

       The class parameter also accepts an array of strings.

       If nothing or an invalid option is specified, Waybar expects i3blocks style output. Values are newline
       separated. This should look like this:

           $text\n$tooltip\n$class*

       class is a CSS class, to apply different styles in style.css

FORMAT REPLACEMENTS
       {}: Output of the script.

       {percentage} Percentage which can be set via a json return-type.

       {icon}: An icon from 'format-icons' according to percentage.
```


# Using library

```c
char *waybar_json(struct Waybar_args *);
```

Arguments:
> `Struct Waybar_args *`: Pointer to a `struct Waybar_args`

Return:
> `char *`: json format on string

### `Waybar_args` fields:
 - `char *text`: text to print instead of `{}` in `"format"` key inside config.
 - `char *tooltip`: "true" OR "false".
 - `char **class`: Array of string of CSS class to apply different styles in `style.css`.
 - `size_t class_len`: Number of string inside `class` field array.
 - `int percentage`: An value between `0` and `100`.

# Example of waybar config file and style.css to use with the [example.c](example.c).
```json
"custom/hddsusage": {
    "format": "{}Go {icon}",
    "format-icons": ["│▁│", "│▃│", "│▅│", "│▇│", "│█│"],
    "exec": "/home/ownesis/waybar_json/a.out",
    "return-type": "json",
    "interval": 10,
},
```

```css
#custom-hddsusage {
    color: white;
}

#custom-hddsusage.caution,
#custom-hddsusage.warning {
    color: yellow;
}

#custom-hddsusage.critical {
    color: red;
}

```
