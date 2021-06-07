  #     #	#     # ########
   #   #	##   ## # #### #
  #######	# # # #	## ## ##
 ## ### ##	# ### # #  ##  #
###########	#     #    ##
# ####### #	# # # # ## ## ##
# #     # #	## # ## # #### #
   ## ##	#     # ########


Thanks for downloading my Space Invaders conversion for PSP.
Please note that this is a Work In Progress and work is still needed.


To install, place the SpaceInvader folder in your GAME folder if running fw 1.50 or in GAME150 if running a OE/M33 firmware.
Other custom firmware and devhook emulation is not known to be compatible but it generally should be.


As for a licence or anything like that....I don't care...reuse and abuse the code or what not however you want :D thats why I included it here :P

Also,if you are reading this and are interested in more PSP homebrew, check out http://www.exophase.com and sign up to the forums :D

and yes,i know my ascii art sucks....its only hashes...lol


Any questions or bug reports, please email me at shatorikiriyama[at]hotmail[dot]co[dot]uk

-----------------------------------------------------
-----------------------------------------------------
Controls - 

D-pad = move ship left and right
X = fire/enter
Triangle = exit/go back
Select = Return to menu

-----------------------------------------------------
-----------------------------------------------------
Themes -

As of version 0.6, space invaders now supports themes.
A theme is basically two images which frame the game screen and make it look nicer.
There is support for custom themes kinda...
To use a custom theme, just replace theme1.png and theme2.png in the theme folder with 
two 90x272 24bit .png image files named theme1.png and theme2.png

-----------------------------------------------------
-----------------------------------------------------

version history - 
-----------------
-----------------
27th Novemeber 2007
0.7   enemy bombs done
      all images are now hard coded into the game :P
      finally got that dam random function of mine to work
      added lives counter at the top right

need to add
-collision detection from the enemy bombs
-add the saucer (should be really easy now that i've got random working :P)
-high scores
-options
-sound
-better error handling in case no themes or menu background are there

note - i really have been flat out with work and college so this on the PSP was really a small thing on the side that i couldnt find the time to work on.at the moment i've had no sleep and have to head to college in about 20 minutes so i hope that someone at least enjoys this.lol.ah well.

-----------------
----------------
15th August 2007
0.6   added base shields
      perfected the invader reset,now you can play til your hearts content :P
      added a drop down effect for a new round
      added a default theme of artwork from Space Invaders
      added a round display screen
      added score display on the game over screen

need to add
-enemy bombs (i did have this done but it kept crashing :\ .the code for it is commented out in the source )
-the ever so elusive saucer
-a method of keeping high scores
-options
-code to render invaders and other images without the need for a resource folder
-sound
-more themes

------------------------
10th August 2007
0.5   added a full array of invaders
      improved collision detection
      near perfected the invaders movement ( more like the arcade version )
      invaders now drop down when they reach the side
      added more menu options
      added a Game Over screen
      added the ability to quit to the XMB from the menu.
      now the players ship is rendered completely in code.

need to add
-base shields
-enemy bombs
-a method of keeping high scores
-options
-code to render invaders and other images without the need for a resource folder
-themes ;]

-------------------------
0.4   removed the grid of invaders as to focus on bullets and collision detection
      added a fire button
      added collision detection
      added score implementation

known glitches
-invader still disappears from screen
-no base shields
-no enemy AI
-if firing at where the invader was destroyed,it adds more points
-------------------------

0.3.1 drew more sprites and editted for less space
      added more invaders,now there's a proper 'grid' of invaders
      removed glitch that caused kamakaze invader :P

known glitches
-invaders still disappear from screen
-no fire button
-no base shields
-no scoring method implemented
-no enemy AI

-------------------------

0.2 inplemented a player ship with controls and the invader now moves across the screen
    implemented a menu system that shall be built on

known glitches
-the invader drops down the screen then reappears eventually disappearing off the side of the screen

-------------------------

 0.1b drawn out two frames of an invader and animated.serious work needed.




                                         MenaceInc