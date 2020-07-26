Elle McFarlane

Gyroscope: moves Doodle player left and right  
Nunchuk: Z button used to shoot enemies  
LCD: visuals  

main.c (aka main depends on all other files):
--initializes: gyroscope data for player movement, nunchuk for shooting,  
screen for visualizations  
--initializes necessary parts and controls time steps for game;  
switches between pause and continue modes.
  
start mode:  
--initializes everything  
--launches player upward at baseline speed between two platforms  

during time step:
--moves player per its velocity (down=negative, up=positive)  
--moves player per gyroscope directions in one axis  
--subtracts gravity acceleration from its velocity  
--if landed on platform->sets velocity back to baseline  
--if landed on platform higher than last->shift frame down (looks like upward)  
to predefined area and build new part of frame; increase score constant amount  
--moves player up a few pixels in normal mode  
--if z button has been pressed->fires bullet (will potential use interrupt for
this if it makes sense)  
--if has collided with enemy->kills player  
(player falls down when it dies)  
--if bullet has collided with enemy->kills enemy, increases score  
(enemy falls down when it dies)  
--if past lower bound->kills player  
--if past upper bound->loads next section  

if have time will implement:  
--moving monsters  
--protection bubble mode  
--weaker tiles that break, move, etc  
--springs, jetpack, flying hat  
--launch off monsters ability  
--more accurate physics simulation (e.g. accerelation when hit platforms)  

game.c  
--creates monster variables in array (and has method to display them as update)  
  --gives them random locations  
--initializes platforms in array (in random locations)  
--has move monsters method (for when frame shifts)  
  --sometimes will move them out of frame to minimize monsters
--hasCollided method  
--used by has player hit monster method  
--and has bullet hit monster method  

player.c:  
dep: bullet.c  
--define struct with coordinates for origin,  
and side length for player square, prev position to override in move   
--initializer  
--draw method (how to draw it, doesn't actually draw)  
--shoot method ("releases bullet object")  
--jump method? or should game control jump?  
--move method (uses step method), possible interrupt method  
--step method (up, down, left, right by given amount)  
--die method (uses step method?)  

monster.c:  
--initializer  
--draw method (how to draw it, doesn't actually draw)  
--die method  
--moveTo method (changes origin to given x and y)  
--step method (up, down, left, right by given amount)  

bullet.c  
--define struct with origin coordinates,
radius, and speed  
--initializer  
 
view.c (called by main)  
dep: lcd, monster.c, platform.c  
--ditto with move platforms method  
--draw all monsters method  
--draw all platforms method  
--draw bullet if initializes  
--draw player  

