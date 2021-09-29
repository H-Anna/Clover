# SSP SakuraScript tags

## Scope commands
Scope commands determine which character will display the talk and execute script commands. Most commonly there are only 1 or 2 characters on screen at a time, so `\0` and `\1` have become prevalent.
### As seen in SSP
|Tag     |Description         |Proposed new name|Notes
|--------|--------------------|-----------------|--
|`\0, \h`|move scope to main character   |`<!p[ID]>`|Assign `ID` 0 to main, 1 to side|
|`\1, \u`|move scope to side character   |-|Discard
|`\p[ID]`|move scope to character with `ID`|-|Discard
I think this would be easier to keep track of. Alternatively, `<!ID>` could also work, or other tags. I'm not very creative right now though.
## Surface commands
These are used to set the surface of the character in scope. Surfaces are a data class that provide information on how to overlay, swap etc. images in such a way that animations can be created. This data is described in surfaces.txt for every shell.
### As seen in SSP
|Tag     |Description                                    |Proposed new name|Notes
|--------|-----------------------------------------------|-----------------|--------------------
|`\sID`  |Change surface, eg. `\s0`. Only 0-9 can be used|
|`\s[ID]`|Change surface. Hide with `\s[-1]`             |
|`\i[ID]`|Use animation belonging to surface.            |
|`\i[ID, wait]`|Wait for animation to complete. No more text is processed until then.|
|`\![anim, clear, ID]`|Stops playback of animation with `ID`.|
|`\![anim, pause, ID]`|Pauses animation playback.|
|`\![anim, resume, ID]`|Resumes animation playback.|
|`\![anim, offset, ID, X, Y]`|Offsets animation using coordinates.|
|`\![anim, add, overlay, ID]`|Overlay surface on current surface.^1^|
|`\![anim, offset, ID, X, Y]`|Offsets animation using coordinates. Valid until `\s[ID]`|
|`\![anim, stop]`|Stop animation.|
|`\__w[animation, ID]`|Wait for animation to complete. Use to delay waiting. Call `\i[ID]` first, then this tag for it to take effect.|
|`\![bind,...]`|Put on or take off clothing from the character.^2^|
|`\![lock,repaint]`|Stops redrawing. Cancelled at end of script. To manually unlock anyway, call `\![lock,repaint, manual]`.|
|`\![unlock,repaint]`|Resumes drawing.|
|`\![set,alignmenttodesktop,ALIGN]`|Set alignment to desktop. ALIGN can be any of the following: `top, bottom, left, right, free, default`. Reset on app exit.|
|`\![set,scaling,PERCENT]`|Zoom in or out on the surface. Negative numbers mirror the surface vertically. Cancelled on app exit.|
|`\![set,scaling,HORIZONTAL, VERTICAL]`|Same as above but in both directions.|
|`\![set,alpha,0-100]`|Sets surface transparency. 0 is fully transparent. Reset on app exit.|
|`\![effect,...]`|Changes the surface using a plugin.|
|`\![effect2,...]`|Same as above?|
|`\![filter,...]`|Surface is run through a filter every time a change is made. Use `\![filter]` to cancel.|
|`\4`|Move character in scope away from the other.|
|`\5`|Move characters closer so they touch.|
|`\![move,...]`|Move character. Too many parameters...|
|`\![moveasync,...]`|Move character asynchronously. Too many parameters...|
|`\![set, position,X,Y,ID]`|Move character at `ID` to specified position and lock it.|
|`\![reset, position]`|Cancels the above.|
|`\![set,zorder,ID,ID,...]`|Lets you micromanage character layering. Eg. 0 will always be on top of 1. Reset on app exit.|
|`\![reset, zorder]`|Cancels the above.|
|`\! [set,sticky-window,ID,ID,...]`|Makes specified windows move as one when dragging or using `\![move]`. Reset on app exit.|
|`\![reset, zorder]`|Cancels the above.|

##### Notes:
1. There are so many variations in parameters that this one tag is really 7 tags in one... anim tags deserve their own document. TODO revisit.
2. Clothing is a beast in and of itself. TODO try to understand it.



