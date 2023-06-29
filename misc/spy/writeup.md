# spy

## Authors

- @CaptainBoggle


## Category
- misc

## Description

ASIO has broken into an alien military network, and discovered that these aliens use what appears to be a modified version of Overwatch PvE to determine the ranks of newly enlisted soldiers. ASIO can see that higher ranking officers are granted immediate clearence to sensitive data, so they need someone to place highly using the stolen software in order to gain more intel on the aliens. After reviewing every Aussie steam account, ASIO has chosen you for the task. Good luck!

The game can be downloaded from [here](https://drive.google.com/drive/folders/1xbwbsRE602dahr353RFQT3HCDpd3a4K8?usp=sharing).

## Difficulty

- Medium

## Solution

<details>
<summary>Spoiler</summary>

### Idea

Beat a rigged game using one of a few possible methods.

### Walkthrough

# Method 1: Cheat Engine

Pause game before taking damage, scan all values. Unpause, walk around a bit without getting hit, and perform another scan
to eliminate all changed values. Get hit once, scan for decreased values, walk around without getting hit, scan for unchanged, 
pick up a health pack, scan for increased etc until you find the health value. Try setting this to a high value, and realise that
when you get hit, it clamps back down to a max health value. Perform a scan to find addressed matching this max health value that aren't changing,
and increase them too. Now, with both overides in place, defeat the enemies.

# Method 2: Pure Skill

Simply outstrafe the enemies and bait them into positions that render them unable to shoot you. 


# Method 3: dnSpy/CE Mono tools

Either of these tools can be used to browse classes and locate the health and maximum health fields by name, then override them directly.

### Flag

`BEGINNER{g1t_gUd_GiT_lM40Box}`

</details>
