#!/usr/bin/python
# -*- coding: utf-8 -*-



import ConfigParser

import pygame
import pygame.locals as pg

import pdb
import random
import time
import sys



def myParse( Comment , my , enemy , action ):
    #global My_stragedy

    global count
    global count_if

    #M = My_stragedy.readline()
    if my[3] == True:
        return
    M = Comment.readline()
    if len(M)==0:
        #pdb.set_trace()
        my[3] = True
        return
    M = M[:-1]
    M_comment = M.split(" ")
    while M_comment[0] == "":
        M_comment.remove("")
    print "[" , count , "]" , my[4] , " -> " , M_comment 
    if M_comment[0] == "build":
        if M_comment[1] == "man":
            #MyCastle[0] += 1
            my[0] += 1
            action['build'] = 'man'
        elif M_comment[1] == "wall":
            #MyCastle[1] += 1
            my[1] += my[0]
            action['build'] = 'wall'
        elif M_comment[1] == "cannon":
            #MyCastle[2] += 1
            my[2] += my[0]
            action['build'] = 'cannon'
        else:
            print "comment "  , count , " input error : " , M_comment[1] 
    elif M_comment[0] == "e_if":
        action['detect'] = True
        Answer = getcondition( M_comment  , my , enemy)
        if Answer == True: 
            return #myParse()
        else:
            while True:
                #M = My_stragedy.readline()
                M = Comment.readline()
                M = M[:-1]
                if M.split(" ")[0] == "e_else" and count_if == 0:
                    count_if = 0
                    break
                elif M.split(" ")[0] == "e_else" and count_if != 0:
                    count_if -= 1
                elif M.split(" ")[0] == "e_if":
                    count_if += 1
                #else:
                    #print "if else count error"
            #myParse()
            return
    elif M_comment[0] == "m_if":
        Answer = getcondition( M_comment , my,enemy)
        if Answer == True: 
            #myParse()
            myParse(Comment , my , enemy , action)
        else:
            while True:
                #M = My_stragedy.readline()
                M = Comment.readline()
                M = M[:-1]
                if M.split(" ")[0] == "m_else" and count_if == 0:
                    count_if = 0
                    break
                elif M.split(" ")[0] == "m_else" and count_if != 0:
                    count_if -= 1
                elif M.split(" ")[0] == "m_if":
                    count_if += 1
                #else:
                    #print "if else count error"
            #myParse()
            myParse(Comment , my , enemy , action)
    elif M_comment[0] == "e_else":
        while True:
            #M = My_stragedy.readline()
            M = Comment.readline()
            M = M[:-1]
            if M.split(" ")[0] == "end":
                break
        #myParse()
        myParse(Comment , my , enemy , action)
    elif M_comment[0] == "m_else":
        while True:
            #M = My_stragedy.readline()
            M = Comment.readline()
            M = M[:-1]
            if M.split(" ")[0] == "end":
                break
        myParse(Comment , my , enemy , action)
    elif M_comment[0] == "fire":
        #EnemyCastle[1] -= MyCastle[2]
        enemy[1] -= my[2]
        action['fire'] = True
    elif M_comment[0] == "end":
        #myParse()
        myParse(Comment , my , enemy , action)
    else:
        print "comment "  , count , " input error : " , M_comment[0] 


def getcondition(M_comment , My , Enemy):
    global EnemyCastle 
    global MyCastle 
    left ,right = True , True
    if M_comment[1] == "e_man":
        left = Enemy[0]
    elif M_comment[1] == "e_wall":
        left = Enemy[1]
    elif M_comment[1] == "e_cannon":
        left = Enemy[2]
    elif M_comment[1] == "m_man":
        left = My[0]
    elif M_comment[1] == "m_wall":
        left = My[1]
    elif M_comment[1] == "m_cannon":
        left = My[2]
    else:
        print "comment "  , count , " input error" 
    if M_comment[3] == "e_man":
        right = Enemy[0]
    elif M_comment[3] == "e_wall":
        right = Enemy[1]
    elif M_comment[3] == "e_cannon":
        right = Enemy[2]
    elif M_comment[3] == "m_man":
        right = My[0]
    elif M_comment[3] == "m_wall":
        right = My[1]
    elif M_comment[3] == "m_cannon":
        right = My[2]
    else:
        print "comment "  , count , " input error" 
    if M_comment[2] == ">":
        Condi = (left > right)
        #pdb.set_trace()
        return Condi
    elif M_comment[2] == "=":
        Condi = (left == right)
        #pdb.set_trace()
        return Condi
    else:
        print "comment "  , count , " input error"


class TileCache(object):
    """Load the tilesets lazily into global cache"""

    def __init__(self,  width=32, height=None):
        self.width = width
        self.height = height or width
        self.cache = {}

    def __getitem__(self, filename):
        """Return a table of tiles, load it from disk if needed."""

        key = (filename, self.width, self.height)
        try:
            return self.cache[key]
        except KeyError:
            tile_table = self._load_tile_table(filename, self.width,
                                               self.height)
            self.cache[key] = tile_table
            return tile_table

    def _load_tile_table(self, filename, width, height):
        """Load an image and split it into tiles."""

        image = pygame.image.load(filename).convert_alpha()
        image_width, image_height = image.get_size()
        tile_table = []
        for tile_x in range(0, image_width/width):
            line = []
            tile_table.append(line)
            for tile_y in range(0, image_height/height):
                rect = (tile_x*width, tile_y*height, width, height)
                line.append(image.subsurface(rect))
        return tile_table


class Soldier_Cache(object):
    """Load the tilesets lazily into global cache"""

    def __init__(self,  width=32, height=None):
        self.width = width
        self.height = height or width
        self.cache = {}

    def __getitem__(self, filename):
        """Return a table of tiles, load it from disk if needed."""

        key = (filename, self.width, self.height)
        try:
            return self.cache[key]
        except KeyError:
            tile_table = self._load_tile_table(filename, self.width,
                                               self.height)
            self.cache[key] = tile_table
            return tile_table

    def _load_tile_table(self, filename, width, height):
        """Load an image and split it into tiles."""

        image = pygame.image.load(filename).convert_alpha()
        image_width, image_height = image.get_size()
        tile_table = []
        for tile_y in range(0, image_height/height):
            rect = (1*width, tile_y*height, width, height)
            line = []
            line.append(image.subsurface(rect))
            tile_table.append(line)
            for tile_x in range(0, image_width/width):
                rect = (tile_x*width, tile_y*height, width, height)
                line.append(image.subsurface(rect))
        return tile_table


class SortedUpdates(pygame.sprite.RenderUpdates):
    """A sprite group that sorts them by depth."""

    def sprites(self):
        """The list of sprites in the group, sorted by depth."""

        return sorted(self.spritedict.keys(), key=lambda sprite: sprite.depth)


class Shadow(pygame.sprite.Sprite):
    """Sprite for shadows."""

    def __init__(self, owner):
        pygame.sprite.Sprite.__init__(self)
        self.image = SPRITE_CACHE["shadow.png"][0][0]
        self.image.set_alpha(64)
        self.rect = self.image.get_rect()
        self.owner = owner

    def update(self, *args):
        """Make the shadow follow its owner."""

        self.rect.midbottom = self.owner.rect.midbottom

class Sprite(pygame.sprite.Sprite):
    """Sprite for animated items and base class for Player."""

    is_player = False

    def __init__(self, pos=(0, 0), frames=None):
        super(Sprite, self).__init__()
        if frames:
            self.frames = frames
        self.image = self.frames[0][0]
        self.rect = self.image.get_rect()
        self.animation = self.stand_animation()
        self.pos = pos

    def _get_pos(self):
        """Check the current position of the sprite on the map."""

        return (self.rect.midbottom[0]-12)/24, (self.rect.midbottom[1]-16)/16

    def _set_pos(self, pos):
        """Set the position and depth of the sprite on the map."""

        self.rect.midbottom = pos[0]*24+12, pos[1]*16+16
        self.depth = self.rect.midbottom[1]

    pos = property(_get_pos, _set_pos)

    def move(self, dx, dy):
        """Change the position of the sprite on screen."""

        self.rect.move_ip(dx, dy)
        self.depth = self.rect.midbottom[1]

    def stand_animation(self):
        """The default animation."""

        while True:
            # Change to next frame every two ticks
            for frame in self.frames[0]:
                self.image = frame
                yield None
                yield None

    def update(self, *args):
        """Run the current animation."""

        self.animation.next()


class Castle(Sprite):
    is_player = False

    def update(self, *args):
        """Run the current animation."""
    def stand_animation(self):
        """The default animation."""
    def xy_image(self, x, y):
        self.image = self.frames[x][y]


class Soldier(Sprite):
    """ Display and animate the player character."""

    is_player = False

    def __init__(self, item, pos=(1, 1)):
        self.frames = Soldier_Cache[item+".png"]
        Sprite.__init__(self, pos)
        self.direction = 0
        self.animation = None
        self.image = self.frames[self.direction][0]

    def walk_animation(self):
        """Animation for the player walking."""

        # This animation is hardcoded for 4 frames and 16x24 map tiles
        for frame in range(4):
            self.image = self.frames[self.direction][frame]
            yield None
            self.move(45*DX[self.direction], 30*DY[self.direction])
            yield None
            self.move(45*DX[self.direction], 30*DY[self.direction])

    def update(self, *args):
        """Run the current animation or just stand there if no animation set."""

        if self.animation is None:
            self.image = self.frames[self.direction][0]
        else:
            try:
                self.animation.next()
            except StopIteration:
                self.animation = None

    def moveto(self, des_x, des_y, direction):
        x, y = self.pos
        self.direction = direction
        if not abs(x-des_x)<3:
            self.animation = self.walk_animation()
            return False
        else:
            self.direction = 0
            return True

class Player(Sprite):
    """ Display and animate the player character."""

    is_player = True

    def __init__(self, pos=(1, 1)):
        self.frames = SPRITE_CACHE["player.png"]
        Sprite.__init__(self, pos)
        self.direction = 2
        self.animation = None
        self.image = self.frames[self.direction][0]

    def walk_animation(self):
        """Animation for the player walking."""

        # This animation is hardcoded for 4 frames and 16x24 map tiles
        for frame in range(4):
            self.image = self.frames[self.direction][frame]
            yield None
            self.move(3*DX[self.direction], 2*DY[self.direction])
            yield None
            self.move(3*DX[self.direction], 2*DY[self.direction])

    def update(self, *args):
        """Run the current animation or just stand there if no animation set."""

        if self.animation is None:
            self.image = self.frames[self.direction][0]
        else:
            try:
                self.animation.next()
            except StopIteration:
                self.animation = None

class Level(object):
    """Load and store the map of the level, together with all the items."""

    def __init__(self, filename="level.map"):
        self.tileset = ''
        self.map = []
        self.items = {}
        self.key = {}
        self.width = 0
        self.height = 0
        self.load_file(filename)

    def load_file(self, filename="level.map"):
        """Load the level from specified file."""

        parser = ConfigParser.ConfigParser()
        parser.read(filename)
        self.tileset = parser.get("level", "tileset")
        self.map = parser.get("level", "map").split("\n")
        for section in parser.sections():
            if len(section) == 1:
                desc = dict(parser.items(section))
                self.key[section] = desc
        self.width = len(self.map[0])
        self.height = len(self.map)
        for y, line in enumerate(self.map):
            for x, c in enumerate(line):
                if not self.is_wall(x, y) and 'sprite' in self.key[c]:
                    self.items[(x, y)] = self.key[c]

    def render(self):
        """Draw the level on the surface."""

        wall = self.is_wall
        tiles = MAP_CACHE[self.tileset]
        image = pygame.Surface((self.width*MAP_TILE_WIDTH, self.height*MAP_TILE_HEIGHT))
        overlays = {}
        for map_y, line in enumerate(self.map):
            for map_x, c in enumerate(line):
                if wall(map_x, map_y):
                    # Draw different tiles depending on neighbourhood
                    if not wall(map_x, map_y+1):
                        if wall(map_x+1, map_y) and wall(map_x-1, map_y):
                            tile = 1, 2
                        elif wall(map_x+1, map_y):
                            tile = 0, 2
                        elif wall(map_x-1, map_y):
                            tile = 2, 2
                        else:
                            tile = 3, 2
                    else:
                        if wall(map_x+1, map_y+1) and wall(map_x-1, map_y+1):
                            tile = 1, 1
                        elif wall(map_x+1, map_y+1):
                            tile = 0, 1
                        elif wall(map_x-1, map_y+1):
                            tile = 2, 1
                        else:
                            tile = 3, 1
                    # Add overlays if the wall may be obscuring something
                    if not wall(map_x, map_y-1):
                        if wall(map_x+1, map_y) and wall(map_x-1, map_y):
                            over = 1, 0
                        elif wall(map_x+1, map_y):
                            over = 0, 0
                        elif wall(map_x-1, map_y):
                            over = 2, 0
                        else:
                            over = 3, 0
                        overlays[(map_x, map_y)] = tiles[over[0]][over[1]]
                else:
                    try:
                        tile = self.key[c]['tile'].split(',')
                        tile = int(tile[0]), int(tile[1])
                    except (ValueError, KeyError):
                        # Default to ground tile
                        tile = 0, 3
                tile_image = tiles[tile[0]][tile[1]]
                image.blit(tile_image,
                           (map_x*MAP_TILE_WIDTH, map_y*MAP_TILE_HEIGHT))
        return image, overlays

    def get_tile(self, x, y):
        """Tell what's at the specified position of the map."""

        try:
            char = self.map[y][x]
        except IndexError:
            return {}
        try:
            return self.key[char]
        except KeyError:
            return {}

    def get_bool(self, x, y, name):
        """Tell if the specified flag is set for position on the map."""

        value = self.get_tile(x, y).get(name)
        return value in (True, 1, 'true', 'yes', 'True', 'Yes', '1', 'on', 'On')

    def is_wall(self, x, y):
        """Is there a wall?"""

        return self.get_bool(x, y, 'wall')

    def is_blocking(self, x, y):
        """Is this place blocking movement?"""

        if not 0 <= x < self.width or not 0 <= y < self.height:
            return True
        return self.get_bool(x, y, 'block')

class Game(object):
    """The main game object."""


    def __init__(self):
        self.screen = pygame.display.get_surface()
        self.pressed_key = None
        self.game_over = False
        self.shadows = pygame.sprite.RenderUpdates()
        self.sprites = SortedUpdates()
        self.overlays = pygame.sprite.RenderUpdates()
        self.use_level(Level())
        self.items = dict()
        self.round_cycle = 50
        self.castle()
        self.m_men = dict()
        self.e_men = dict()

    def use_level(self, level):
        """Set the level as the current one."""

        self.shadows = pygame.sprite.RenderUpdates()
        self.sprites = SortedUpdates()
        self.overlays = pygame.sprite.RenderUpdates()
        self.level = level
        # Populate the game with the level's objects
        for pos, tile in level.items.iteritems():
            if tile.get("player") in ('true', '1', 'yes', 'on'):
                sprite = Player(pos)
                self.player = sprite
            else:
                sprite = Sprite(pos, SPRITE_CACHE[tile["sprite"]])
            self.sprites.add(sprite)
            self.shadows.add(Shadow(sprite))
        # Render the level map
        self.background, overlays = self.level.render()
        # Add the overlays for the level map
        for (x, y), image in overlays.iteritems():
            overlay = pygame.sprite.Sprite(self.overlays)
            overlay.image = image
            overlay.rect = image.get_rect().move(x*24, y*16-16)

    def control(self):
        """Handle the controls of the game."""

        keys = pygame.key.get_pressed()

        def pressed(key):
            """Check if the specified key is pressed."""

            return self.pressed_key == key or keys[key]

        def walk(d):
            """Start walking in specified direction."""
            
            x, y = self.player.pos
            self.player.direction = d
            if not self.level.is_blocking(x+DX[d], y+DY[d]):
                self.player.animation = self.player.walk_animation()

        if pressed(pg.K_UP):
            walk(0)
        elif pressed(pg.K_DOWN):
            walk(2)
        elif pressed(pg.K_LEFT):
            walk(3)
        elif pressed(pg.K_RIGHT):
            walk(1)
        self.pressed_key = None

    def castle(self):
        for x in range (0,3):
            for y in range (0,4):
                sprite = Castle((x+3,y+4), MAP_CACHE['castle.png'])
                sprite.xy_image(x,y)
                sprite.depth=x+3*y
                self.sprites.add(sprite)

                sprite = Castle((x+46,y+4), MAP_CACHE['castle.png'])
                sprite.xy_image(x,y)
                sprite.depth=x+3*y
                self.sprites.add(sprite)

    def build_wall(self, item, stage ,stop):
        if stop:
            return
        if item == 'm_wall':
            x=16
        else:
            x=34

        if stage == 0:
            if item+'2_s' in self.items:
                return
            if item+'2' in self.items:
                return
            sprite = Sprite((x,2), SPRITE_CACHE['smoke.png'])
            self.items[item+'2_s'] = sprite 
            self.sprites.add(sprite)

            sprite = Sprite((x,3), SPRITE_CACHE['smoke.png'])
            self.items[item+'3_s'] = sprite 
            self.sprites.add(sprite)

            sprite = Sprite((x,4), SPRITE_CACHE['smoke.png'])
            self.items[item+'4_s'] = sprite 
            self.sprites.add(sprite)

            sprite = Sprite((x,5), SPRITE_CACHE['smoke.png'])
            self.items[item+'5_s'] = sprite 
            self.sprites.add(sprite)

            sprite = Sprite((x,7), SPRITE_CACHE['smoke.png'])
            self.items[item+'7_s'] = sprite 
            self.sprites.add(sprite)

            sprite = Sprite((x,8), SPRITE_CACHE['smoke.png'])
            self.items[item+'8_s'] = sprite 
            self.sprites.add(sprite)

            sprite = Sprite((x,9), SPRITE_CACHE['smoke.png'])
            self.items[item+'9_s'] = sprite 
            self.sprites.add(sprite)

            sprite = Sprite((x,10), SPRITE_CACHE['smoke.png'])
            self.items[item+'10_s'] = sprite 
            self.sprites.add(sprite)
        else:
            if item+'2' in self.items:
                return
            self.remove(item+'2_s')
            sprite = Castle((x,2), SPRITE_CACHE['wall.png'])
            sprite.xy_image(0,0)
            self.items[item+'2'] = sprite #m_wall2
            self.sprites.add(sprite)

            self.remove(item+'3_s')
            sprite = Castle((x,3), SPRITE_CACHE['wall.png'])
            sprite.xy_image(0,2)
            self.items[item+'3'] = sprite #m_wall3
            self.sprites.add(sprite)

            self.remove(item+'4_s')
            sprite = Castle((x,4), SPRITE_CACHE['wall.png'])
            sprite.xy_image(0,2)
            self.items[item+'4'] = sprite #m_wall4
            self.sprites.add(sprite)

            self.remove(item+'5_s')
            sprite = Castle((x,5), SPRITE_CACHE['wall.png'])
            sprite.xy_image(0,4)
            self.items[item+'5'] = sprite #m_wall5
            self.sprites.add(sprite)

            self.remove(item+'7_s')
            sprite = Castle((x,7), SPRITE_CACHE['wall.png'])
            sprite.xy_image(0,0)
            self.items[item+'7'] = sprite #m_wall7
            self.sprites.add(sprite)

            self.remove(item+'8_s')
            sprite = Castle((x,8), SPRITE_CACHE['wall.png'])
            sprite.xy_image(0,2)
            self.items[item+'8'] = sprite #m_wall8
            self.sprites.add(sprite)

            self.remove(item+'9_s')
            sprite = Castle((x,9), SPRITE_CACHE['wall.png'])
            sprite.xy_image(0,2)
            self.items[item+'9'] = sprite #m_wall9
            self.sprites.add(sprite)

            self.remove(item+'10_s')
            sprite = Castle((x,10), SPRITE_CACHE['wall.png'])
            sprite.xy_image(0,4)
            self.items[item+'10'] = sprite #m_wall10
            self.sprites.add(sprite)

    def remove_wall(self, item):
        self.remove(item+'2')
        self.remove(item+'3')
        self.remove(item+'4')
        self.remove(item+'5')
        self.remove(item+'7')
        self.remove(item+'8')
        self.remove(item+'9')
        self.remove(item+'10')

    def build_man(self,item):
        if item == 'm_man':
            sprite = Soldier(item,(6,6+len(self.m_men)))
            self.m_men[str(len(self.m_men))]=sprite
        else:
            if len(self.e_men)>0:                                  ####################demo
                return
            sprite = Soldier(item,(45,6+len(self.m_men)))
            self.e_men[str(len(self.e_men))]=sprite
        self.sprites.add(sprite)
            
    def build(self, item , stage , stop):
        if item in ('m_wall','e_wall'):
            self.build_wall(item, stage, stop)
            return
        if item in ('m_man','e_man'):
            return

        if item in self.items:
            return

        if item == 'm_cannon':
            x,y = 17,8
        elif item == 'e_cannon':
            x,y = 33,8
        elif item == 'm_bullet':
            x,y = 18,8
        else:
            x,y = 32,8

        if stage == 0:
            if item+'_s' in self.items:
                return
            sprite = Sprite((x,y), SPRITE_CACHE['smoke.png'])
            self.items[item+'_s']=sprite
            self.sprites.add(sprite)
        elif stage == 1:
            self.remove(item+'_s')
            sprite = Sprite((x,y), SPRITE_CACHE[item+'.png'])
            if item in ('e_cannon','m_cannon'):
                sprite.move(-7,0)
            self.items[item]=sprite
            self.sprites.add(sprite)
            
        
        
    def fire(self, item , stage):
        if item == 'm_fire':
            x,y = 18,8
            bullet = 'm_bullet'
            speed = 30
            wall = 'e_wall'
            castle_pos = 46
            life = EnemyCastle[1]
        else:
            x,y = 32,8
            bullet='e_bullet'
            speed = -30
            wall = 'm_wall'
            castle_pos = 5
            life = MyCastle[1]
        if stage == 0:
            if bullet not in self.items:
                sprite = Sprite((x,y), SPRITE_CACHE[bullet+'.png'])
                self.items[bullet]=sprite
                sprite.move(0,-8)
                self.sprites.add(sprite)
            else:
                self.sprites.remove(self.items[bullet])
                self.items[bullet].move(speed,0)
                self.sprites.add(self.items[bullet])

            if item in self.items:
                return 0
            sprite = Sprite((x,y), SPRITE_CACHE[item+'.png'])
            sprite.move(0,-8)
            self.items[item]=sprite
            self.sprites.add(sprite)

        elif stage == 1:
            if bullet not in self.items:
                return 0
            if abs(self.items[bullet].pos[0]-castle_pos-1) < 2:
                self.crash(bullet)
                return 2
            elif wall+'2' in self.items:
                if life == 0 and abs(self.items[bullet].pos[0]-self.items[wall+'2'].pos[0]+1) < 0.5:
                    self.crash(bullet,wall)
                    return 1
                elif life < 0 and abs(self.items[bullet].pos[0]-self.items[wall+'2'].pos[0]+1) < 0.5:
                    self.crash('',wall)
                    return 1
                elif life > 0 and abs(self.items[bullet].pos[0]-self.items[wall+'2'].pos[0]+1) < 0.5:
                    self.crash(bullet)
                    return 1
            
            self.remove(item)
            self.sprites.remove(self.items[bullet])
            self.items[bullet].move(speed,0)
            self.sprites.add(self.items[bullet])

    def crash(self, bullet , item = ''):
        self.remove_wall(item)
        self.remove(bullet)
        #raw_input('Press <ENTER> to continue')
        

    def remove(self, item):
        if item not in self.items:
            return
        self.sprites.remove(self.items[item])
        del self.items[item]

    def detect(self, header, ret):
        if header == 'm_':
            if ret:
                if self.m_men['0'].animation is None:
                    return self.m_men['0'].moveto(6,6,1)
            else:
                if self.m_men['0'].animation is None:    
                    return self.m_men['0'].moveto(34,6,2) 
        else:
            if ret:
                if self.e_men['0'].animation is None:
                    return self.e_men['0'].moveto(45,6,2)
            else:
                if self.e_men['0'].animation is None:
                    return self.e_men['0'].moveto(16,6,1) 


    def main(self):
        """Run the main loop."""

        clock = pygame.time.Clock()
        # Draw the whole screen initially

        # Display some text
        #font = pygame.font.Font(None, 36)
        #text = font.render("Hello There", 1, (10, 10, 10))
        #textpos = text.get_rect()
        #textpos.centerx = self.background.get_rect().centerx
        #self.background.blit(text, textpos)

        self.screen.blit(self.background, (0, 0))
        self.overlays.draw(self.screen)
        pygame.display.flip()

        


        global count
        global count_if

        m_action = dict()
        e_action = dict()
        m_stop = False
        e_stop = False
        m_win = False
        e_win = False

        # The main game loop
        while not self.game_over:
            m_action['build'] = None
            m_action['fire'] = None
            e_action['build'] = None
            e_action['fire'] = None
            m_action['detect'] = None
            e_action['detect'] = None
            print "=============  " , count , "round  =========================="
            myParse(My_stragedy , MyCastle , EnemyCastle, m_action)
            if mode == "Dual":
                myParse(Enemy_stragedy , EnemyCastle , MyCastle, e_action)
            elif mode == "single":
                move = random.randint(0,3)
                if move == 0 :
                    EnemyCastle[0] += 1
                elif move == 1 :
                    EnemyCastle[1] += EnemyCastle[0]
                elif move == 2 :
                    EnemyCastle[2] += EnemyCastle[0]
                elif move == 3 :
                    MyCastle[1] -= EnemyCastle[2] 
            else:
                print "mode error"

            pygame.display.set_caption("Round "+str(count))
            count += 1     

            if m_action['build'] == 'man':
                self.build_man('m_man')
            if e_action['build'] == 'man':
                self.build_man('e_man')

            print MyCastle
            print EnemyCastle
            print " " 


            #animation

            round_clock=0
            stage_b = 0
            stage_f = 0
            m_detect_ret = False
            e_detect_ret = False
            while round_clock<self.round_cycle:
                round_clock += 1
                if m_win:
                    raw_input('Press to end')

                if round_clock > self.round_cycle*0.2:
                    stage_b = 1
                if round_clock > self.round_cycle*0.04:
                    stage_f = 1
                

                if not m_action['build'] == None:
                    self.build('m_'+m_action['build'],stage_b, m_stop)

                if not e_action['build'] == None:
                    self.build('e_'+e_action['build'],stage_b, e_stop)

                if not m_action['fire'] == None:
                    state = self.fire('m_fire',stage_f)
                    if not state == 0:
                        e_stop = True
                    if state == 2:
                        m_win = True

                if not e_action['fire'] == None:
                    state = self.fire('e_fire',stage_f)
                    if not state == 0:
                        m_stop = True
                    if state == 2:
                        e_win = True

                if not m_action['detect'] == None:
                    if self.detect('m_',m_detect_ret):
                        m_detect_ret = True

                if not e_action['detect'] == None:
                    if self.detect('e_',e_detect_ret):
                        e_detect_ret = True


                # Don't clear shadows and overlays, only sprites.
                self.sprites.clear(self.screen, self.background)
                self.sprites.update()
                # If the player's animation is finished, check for keypresses
                #if self.player.animation is None:
                    #self.control()
                #    self.player.update()
                
                self.shadows.update()
                # Don't add shadows to dirty rectangles, as they already fit inside
                # sprite rectangles.
                self.shadows.draw(self.screen)
                dirty = self.sprites.draw(self.screen)
                # Don't add ovelays to dirty rectangles, only the places where
                # sprites are need to be updated, and those are already dirty.
                self.overlays.draw(self.screen)
                # Update the dirty areas of the screen
                pygame.display.update(dirty)
                # Wait for one tick of the game clock
                clock.tick(15)

                if m_win : 
                    # Display some text
                    basicfont = pygame.font.SysFont(None, 48)
                    text = basicfont.render('You Win!', True, (255, 0, 0))
                    textrect = text.get_rect()
                    textrect.centerx = self.screen.get_rect().centerx
                    textrect.centery = self.screen.get_rect().centery
 
                    #self.screen.fill((255, 255, 255))
                    self.screen.blit(text, textrect)

                    image = pygame.image.load('crash.png').convert_alpha()
                    self.screen.blit(image,(46*24,58))
                    pygame.display.flip()

                # Process pygame events
                for event in pygame.event.get():
                    if event.type == pg.QUIT:
                        self.game_over = True
                    elif event.type == pg.KEYDOWN:
                        self.pressed_key = event.key




# Motion offsets for particular directions
#      S  W  E   N
DX = [ 0,-1, 1, 0]
DY = [ 1, 0, 0,-1]

# Dimensions of the map tiles
MAP_TILE_WIDTH, MAP_TILE_HEIGHT = 24, 16


if __name__ == "__main__":
    #             man ,  wall , connon, ifFinish
    MyCastle    = [ 0 , 0 , 0 , False , "User"]
    EnemyCastle = [ 0 , 0 , 0 , False , "Com1"]



    My_stragedy = open( sys.argv[1] , "r")
    Enemy_stragedy = 0 

    count = 1
    count_if = 0

    if len(sys.argv) == 2:
        print "Single player "
        mode = "single"
    elif len(sys.argv) == 3:
        print "Dual players"
        mode = "Dual"
    else:
        print "Input error"
        print "python testgame.py <Players1's program> [Player2's program] "

    #print 'Number of arguments:', len(sys.argv), 'arguments.'
    #print 'Argument List:', str(sys.argv)



    if mode == "Dual":
        Enemy_stragedy = open( sys.argv[2] , "r")
    
    #My_finish = False
    #Enemy_finish = False

    #pdb.set_trace()
    
    #E = Enemy_stragedy.readline()
    #E_comment = E.split(" ")
    

    SPRITE_CACHE = TileCache()
    Soldier_Cache = Soldier_Cache()
    MAP_CACHE = TileCache(MAP_TILE_WIDTH, MAP_TILE_HEIGHT)
    TILE_CACHE = TileCache(32, 32)
    pygame.init()
    pygame.display.set_mode((1224, 190))
    pygame.display.set_caption("Legoram")


    Game().main()


