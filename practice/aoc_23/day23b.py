from ipython_startup.imports import *

inp_o = '''\
#.###########################################################################################################################################
#.#...#...#.....###...#.......###...#####...#...#...#...#...#...#.......#...#.....#.....#.......#...#...#...###...#.....#.....#.............#
#.#.#.#.#.#.###.###.#.#.#####.###.#.#####.#.#.#.#.#.#.#.#.#.#.#.#.#####.#.#.#.###.#.###.#.#####.#.#.#.#.#.#.###.#.#.###.#.###.#.###########.#
#.#.#.#.#.#.#...#...#.#...#...#...#...#...#...#.#.#.#.#.#.#...#...#.....#.#.#...#.#.#...#.....#.#.#...#.#.#...#.#.#.#...#...#.#.....#.....#.#
#.#.#.#.#.#.#.###.###.###.#.###.#####.#.#######.#.#.#.#.#.#########.#####.#.###.#.#.#.#######.#.#.#####.#.###.#.#.#.#.#####.#.#####.#.###.#.#
#...#.#.#.#.#...#.#...###.#...#.#...#.#.....#...#.#...#.#.#.........#.....#...#.#.#.#...#...#.#.#.#.....#.#...#.#.#.#...#...#.#.....#...#...#
#####.#.#.#.###.#.#.#####.###.#.#.#.#.#####.#.###.#####.#.#.#########.#######.#.#.#.###.#.#.#.#.#.#.#####.#.###.#.#.###.#.###.#.#######.#####
#.....#.#.#.###...#.#...#.#...#.#.#...#.....#.#...#...#.#.#.###.....#.....#...#.#.#.#...#.#.#.#.#.#...###.#...#.#.#...#...#...#.....#...#...#
#.#####.#.#.#######.#.#.#.#.###.#.#####.#####.#.###.#.#.#.#.###.###.#####.#.###.#.#.#.###.#.#.#.#.###.###.###.#.#.###.#####.#######.#.###.#.#
#.#...#.#...#.....#.#.#.#.#...#.#.>.>.#.....#.#.#...#...#.#...#.#...###...#.#...#...#.#...#...#.#.#...#...#...#.#.###.#.....#...#...#...#.#.#
#.#.#.#.#####.###.#v#.#.#.###.#.###v#.#####.#.#.#.#######.###.#.#.#####.###.#.#######.#.#######.#.#.###.###.###.#.###.#.#####.#.#.#####.#.#.#
#...#...#...#.#...#.>.#.#.###.#.#...#.......#.#.#.#.>.>.#.#...#.#...#...#...#.#.....#.#.....#...#.#.###...#.#...#...#.#.#...#.#.#...#...#.#.#
#########.#.#.#.###v###.#.###.#.#.###########.#.#.#.#v#.#.#.###.###.#.###.###.#.###.#.#####.#.###.#.#####.#.#.#####.#.#.#.#.#.#.###.#.###.#.#
###.....#.#...#.#...###.#.#...#.#...###...###...#...#.#.#.#...#...#.#.#...###...#...#.#...#.#...#.#.>.>...#.#.#.....#.#.#.#.#.#.#...#.....#.#
###.###.#.#####.#.#####.#.#.###.###.###.#.###########.#.#.###.###.#.#.#.#########.###.#.#.#.###.#.###v#####.#.#.#####.#.#.#.#.#.#.#########.#
#...#...#.....#.#.....#.#.#.....###...#.#.....#.......#...###...#.#.#.#.#.>.>.#...#...#.#.#.#...#.###.#.....#.#.#...#.#.#.#.#.#.#.#.........#
#.###.#######.#.#####.#.#.###########.#.#####.#.###############.#.#.#.#.#.#v#.#.###.###.#.#.#.###.###.#.#####.#.#.#.#.#.#.#.#.#.#.#.#########
#...#.........#.....#.#.#.#...........#.###...#.......###.......#.#.#.#...#.#.#...#.#...#...#...#.#...#.#...#.#.#.#.#.#.#.#.#.#.#.#.#...#...#
###.###############.#.#.#.#.###########.###.#########.###.#######.#.#.#####.#.###.#.#.#########.#.#.###.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#
###...............#.#.#.#.#...#.......#...#.#...#...#...#...#...#.#...###...#.....#...#...#.....#.#...#.#.#.#.#.#.#.#.#.#.#.#.#.#.#...#.#.#.#
#################.#.#.#.#.###.#.#####.###.#.#.#.#.#.###.###.#.#.#.#######.#############.#.#.#####.###.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#####.#.#.#
#.................#...#...###.#.#.....#...#...#.#.#.#...###...#.#.#.......#...#...#.....#.#.#.....#...#...#...#.#.#...#.#.#...#...#...#...#.#
#.###########################.#.#.#####.#######.#.#.#.#########.#.#.#######.#.#.#.#.#####.#.#.#####.###########.#.#####.#.#########.#.#####.#
#.................###...#####...#.....#.#.......#.#...#...#.....#.#...#...#.#...#.#.#.....#...#.....#...###...#.#.....#...###...#...#.#...#.#
#################.###.#.#############.#.#.#######.#####.#.#.#####.###.#.#.#.#####.#.#.#########.#####.#.###.#.#.#####.#######.#.#.###.#.#.#.#
#.......#...#...#.#...#...#...#.....#...#.....###.....#.#.#.....#...#...#.#.#.....#.#.#.....#...#...#.#...#.#.#.......#...#...#.#.###...#...#
#.#####.#.#.#.#.#.#.#####.#.#.#.###.#########.#######.#.#.#####.###.#####.#.#.#####.#.#.###.#.###.#.#.###.#.#.#########.#.#.###.#.###########
#.#...#...#...#...#.#.....#.#.#...#.###.......#.......#.#...###.....###...#.#.#.....#.#.#...#.....#...###...#...###...#.#.#...#.#...........#
#.#.#.#############.#.#####.#.###.#.###.#######.#######.###.###########.###.#.#.#####.#.#.#####################.###.#.#.#.###.#.###########.#
#...#.#...#...#...#.#...#...#...#.#.....#.....#...#...#.#...#.........#.....#.#.#.....#.#.#...#.......#.........#...#.#.#.#...#...#.......#.#
#####.#.#.#.#.#.#.#.###.#.#####.#.#######.###.###.#.#.#.#.###.#######.#######.#.#.#####.#.#.#.#.#####.#.#########.###.#.#.#.#####.#.#####.#.#
#.....#.#.#.#.#.#.#...#.#.#.....#...#...#.#...###...#...#.#...#.......###...#...#...#...#.#.#.#...#...#.#.......#...#...#...#####...#...#.#.#
#.#####.#.#.#v#.#.###.#.#.#.#######.#.#.#.#.#############.#.###.#########.#.#######.#.###.#.#.###.#.###.#.#####.###.#################.#.#.#.#
#.......#...#.>.#...#.#.#.#...#...#...#...#.###...###.....#...#.#...#.....#.#.......#...#.#.#.....#...#...#...#...#.#...............#.#.#...#
#############v#####.#.#.#.###.#.#.#########.###.#.###v#######.#.#.#.#.#####.#.#########.#.#.#########.#####.#.###.#.#.#############.#.#.#####
#.........###.....#...#...#...#.#.......#...#...#.#.>.>.#...#.#.#.#.#.....#.#.#...#...#.#.#.......#...#...#.#...#.#.#.#.............#.#.....#
#.#######.#######.#########.###.#######.#.###.###.#.#v#.#.#.#.#.#.#.#####.#.#.#.#.#.#.#.#.#######.#.###.#.#v###.#.#.#.#.#############.#####.#
#.......#.#.....#.....#.....###.......#.#...#...#...#.#.#.#.#.#.#.#...###.#.#...#.#.#.#.#...#...#.#...#.#.>.>.#...#...#...............#...#.#
#######.#.#.###.#####.#.#############.#.###v###.#####.#.#.#.#.#.#.###.###.#.#####v#.#.#.###.#.#.#.###.#.###v#.#########################.#.#.#
#...###.#.#...#.#.....#.#.....#...#...#.#.>.>...#.....#...#.#.#...###...#.#.#...>.>.#...###.#.#.#.#...#.#...#.#...#...#...#.........#...#.#.#
#.#.###.#.###.#.#.#####.#.###.#.#.#.###.#.#v#####.#########.#.#########.#.#.#.###v#########.#.#.#.#.###.#.###.#.#.#.#.#.#.#v#######.#.###.#.#
#.#...#.#.###.#.#.....#.#.###.#.#...###...#.....#...#...###...#.......#.#.#.#...#.#...#...#.#.#.#.#.#...#.###.#.#.#.#.#.#.>.###...#...###...#
#.###.#.#.###.#.#####.#.#.###.#.###############.###.#.#.#######.#####.#.#.#.###.#.#.#.#.#.#.#.#.#.#.#.###.###.#.#.#.#.#.###v###.#.###########
#...#.#.#...#.#.......#.#.#...#.###...###...#...###...#.........#.....#...#.....#...#...#.#.#.#.#.#.#.###...#...#.#.#.#.###.....#.#...#...###
###.#.#.###.#.#########.#.#.###.###.#.###.#.#.###################.#######################.#.#.#.#.#.#.#####.#####.#.#.#.#########.#.#.#.#.###
#...#.#...#.#.#.......#.#.#...#.#...#.#...#.#.#.................#.....#.................#.#...#...#...#.....#...#...#...#.........#.#...#...#
#.###.###.#.#.#.#####.#.#.###.#.#.###.#.###.#.#.###############.#####.#.###############.#.#############.#####.#.#########.#########.#######.#
#...#.....#...#.#.....#...#...#.#...#...###...#...#...#.......#.#.....#...........#...#...#...###.....#.....#.#.###...###.........#.#.......#
###.###########.#.#########.###.###.#############.#.#.#.#####.#.#.###############.#.#.#####.#.###.###.#####.#.#.###.#.###########.#.#.#######
###.............#.....#...#.....###...#...###...#...#...#.....#...#...#...#...###...#...#...#...#...#.#.....#.#.#...#...#.........#.#.#...###
#####################.#.#.###########.#.#.###.#.#########.#########.#.#.#.#.#.#########.#.#####.###.#.#.#####.#.#.#####.#.#########.#.#.#.###
#.....................#.#.#.....#...#...#.....#.#...#.....###...###.#.#.#.#.#.#...#.....#.....#.###.#.#...###.#.#...#...#.........#.#...#...#
#.#####################.#.#.###.#.#.###########.#.#.#.#######.#.###.#.#.#.#.#.#.#.#.#########.#.###.#.###v###.#.###.#.###########v#.#######.#
#.#.....#.............#.#.#...#.#.#.............#.#.#.......#.#.###.#.#.#.#.#.#.#.#...#####...#.#...#...>.>.#.#.#...#...#.....#.>.#.#.......#
#.#.###.#.###########.#.#.###.#.#v###############.#.#######.#.#.###.#.#.#.#.#.#.#.###v#####.###.#.#######v#.#.#.#.#####.#.###.#.#v#.#.#######
#...#...#.#.....#...#.#.#.#...#.>.>...#...###.....#...#.....#.#.###.#.#.#.#.#.#.#...>.>.#...###.#.#.......#...#...#.....#...#...#.#.#.#...###
#####.###.#.###.#.#.#.#.#.#.#####v###.#.#.###.#######.#.#####.#.###.#.#.#.#.#.#.#####v#.#.#####.#.#.###############.#######.#####.#.#.#.#.###
#...#.....#...#...#...#.#...###...###...#...#.#.......#.....#.#.#...#.#.#.#.#.#...#...#...#...#...#.....#...###.....#...#...#.....#.#...#...#
#.#.#########.#########.#######.###########.#.#.###########.#.#.#.###.#.#.#.#.###.#.#######.#.#########.#.#.###.#####.#.#.###.#####.#######.#
#.#.#...#...#...#.....#.......#.......#...#...#...###...#...#.#.#...#.#.#.#.#.#...#.........#.#...#####...#...#...#...#...###.......#...#...#
#.#.#.#.#.#.###.#.###.#######.#######.#.#.#######.###.#.#v###.#.###.#.#.#.#.#.#.#############.#.#.###########.###.#.#################.#.#.###
#.#...#...#.....#.#...#...#...#.......#.#.......#...#.#.>.>...#.#...#.#.#.#.#.#...###.......#.#.#.............#...#.#.................#...###
#.###############.#.###.#.#.###.#######.#######.###.#.###v#####.#.###.#.#.#.#.###.###.#####.#.#.###############.###.#.#######################
#...#.....#...###.#.....#...###...#...#...#.....#...#...#.#...#...###...#...#.#...#...#...#...#.............###.#...#.......................#
###.#.###.#.#v###.###############.#.#.###.#.#####.#####.#.#.#.###############.#.###.###.#.#################.###.#.#########################.#
###.#.###.#.#.>...#...........#...#.#.....#.#...#...#...#.#.#.........#.......#.###.....#.#.......#.......#...#.#.#...###...#...............#
###.#.###.#.#v#####.#########.#.###.#######.#.#.###.#.###.#.#########.#.#######.#########.#.#####.#.#####.###.#.#.#.#.###.#.#.###############
#...#...#...#...#...#.........#.....#.......#.#...#.#.###.#.#.....#...#.......#...#.......#.#.....#.....#.....#...#.#.....#...#...#...###...#
#.#####.#######.#.###.###############.#######.###.#.#.###.#.#.###.#.#########.###.#.#######.#.#########.###########.###########.#.#.#.###.#.#
#.#.....#.....#...#...#...#...#...###.........#...#.#.###...#...#...#####...#.....#.........#...###...#.........###.....#.....#.#...#.#...#.#
#.#.#####.###.#####.###.#.#.#.#.#.#############.###.#.#########.#########.#.###################.###.#.#########.#######.#.###.#.#####.#.###.#
#...#...#...#.......###.#.#.#.#.#...#...........###...#...#...#...#...###.#.###.......#.........#...#.#.........#...###...###...#.....#.#...#
#####.#.###.###########.#.#.#.#.###.#.#################.#.#.#.###.#.#.###.#.###.#####.#.#########.###.#.#########.#.#############.#####.#.###
#.....#.....#.........#.#...#.#...#.#...#...#...###...#.#.#.#.###...#.....#...#.....#.#.........#...#.#.....#.....#.#...###...#...#.....#.###
#.###########.#######.#.#####.###.#.###.#.#.#.#.###.#.#.#.#.#.###############.#####.#.#########.###.#.#####.#.#####.#.#.###.#.#.###.#####.###
#.......#...#.#.......#.....#...#.#.###...#...#...#.#.#.#.#.#...#.....#.....#.#.....#...........###.#.......#.#.....#.#.#...#.#.....#...#...#
#######.#.#.#.#.###########.###.#.#.#############.#.#.#.#.#.###.#.###.#.###.#.#.###################.#########.#.#####.#.#.###.#######.#.###.#
#.......#.#...#.........#...#...#.#.#...###.......#.#.#.#.#.#...#.###...###...#.......#...###.....#.....#...#.#.#...#.#.#.#...#...###.#.#...#
#.#######.#############.#.###.###.#.#.#.###v#######.#.#.#.#.#.###v###################.#.#.###.###.#####v#.#.#.#.#.#.#.#.#.#.###.#.###.#.#v###
#.......#.#.............#...#...#.#.#.#...>.>...#...#.#.#...#...>.>.#...#...###.......#.#...#...#.#...>.>.#.#.#.#.#.#.#.#.#...#.#.....#.>.###
#######.#.#.###############.###.#.#.#.#####v###.#.###.#.#########v#.#.#.#.#.###.#######.###.###.#.#.###v###.#.#.#.#.#.#.#.###.#.#########v###
###...#...#.........###...#...#...#...###...#...#.#...#...#...#...#...#...#...#.........#...###.#.#...#...#.#.#.#.#.#.#.#.#...#.#...###...###
###.#.#############.###.#.###.###########.###.###.#.#####.#.#.#.#############.###########.#####.#.###.###.#.#.#.#.#.#.#.#.#.###.#.#.###.#####
#...#...............#...#.#...#...........###...#.#.#.....#.#.#...#...........#...#.......###...#.#...#...#.#.#.#.#.#.#.#.#.....#.#...#.#...#
#.###################.###.#.###.###############.#.#.#.#####.#.###.#.###########.#.#.#########.###.#.###.###.#.#.#.#.#.#.#.#######.###.#.#.#.#
#.#...........#...#...#...#...#.............#...#.#...###...#.#...#...###...#...#.#.........#...#.#.###...#...#...#...#...#.....#.#...#...#.#
#.#.#########.#.#v#.###.#####.#############.#.###.#######.###.#.#####.###.#.#.###.#########.###.#.#.#####.#################.###.#.#.#######.#
#.#.###...###...#.>.###.......#...###.......#.....###...#...#.#.....#...#.#.#.#...#...###...#...#.#...#...#...#...#...#...#...#...#...#...#.#
#.#.###.#.#######v#############.#.###.###############.#.###.#.#####.###.#.#.#.#.###.#.###v###.###.###.#.###.#.#.#.#.#.#.#.###.#######.#.#.#.#
#...#...#.......#.........#.....#.....#...###...###...#.....#.#.....#...#.#.#.#...#.#...>.>.#...#.....#.....#.#.#...#...#.###.......#.#.#.#.#
#####.#########.#########.#.###########.#.###.#.###.#########.#.#####.###.#.#.###.#.#####v#.###.#############.#.#########.#########.#.#.#.#.#
#.....#.......#.#...#...#.#.............#.....#.#...#...#...#.#...#...#...#...#...#...#...#.#...###...........#.........#.#...#...#.#.#.#...#
#.#####.#####.#.#.#.#.#.#.#####################.#.###.#.#.#.#.###.#.###.#######.#####.#.###.#.#####.###################.#.#.#.#.#.#.#.#.#####
#.#.....#.....#...#...#...#.......#.............#.....#...#.#.....#...#.......#.....#.#...#.#.....#.............#.......#...#...#.#.#.#.....#
#.#.#####.#################.#####.#.#######################.#########.#######.#####.#.###.#.#####.#############.#.###############.#.#.#####.#
#...#...#.#...#.......#...#...#...#...........#.......#...#.#...#...#.#.......#.....#.#...#.......#.......#.....#...#...#...#...#...#.......#
#####.#.#.#.#.#.#####.#.#.###.#.#############.#.#####.#.#.#.#.#.#.#.#.#.#######.#####.#.###########.#####.#.#######.#.#.#.#.#.#.#############
#...#.#.#...#...#.....#.#.#...#...###...#.....#.....#...#...#.#.#.#.#...#...###.......#.#...#.....#.#...#...###...#.#.#.#.#...#.###.........#
#.#.#.#.#########.#####.#.#.#####.###.#.#.#########.#########.#.#.#.#####.#.###########.#.#.#.###.#.#.#.#######.#.#.#.#.#.#####.###.#######.#
#.#...#.#...#...#.....#.#.#...#...#...#...###.....#...#...###.#.#.#.#...#.#.###...#...#.#.#.#.#...#.#.#.......#.#.#...#...#...#.....#...#...#
#.#####.#.#.#.#.#####.#.#.###.#.###.#########.###.###.#.#.###.#.#.#.#.#.#.#.###.#.#.#.#v#.#.#.#.###.#.#######.#.#.#########.#.#######.#.#.###
#.....#.#.#...#.#.....#.#...#.#.###...###...#...#.###.#.#.#...#.#.#.#.#.#.#.#...#.#.#.>.>.#...#.###...#.......#.#.#.........#.........#...###
#####.#.#.#####.#.#####.###.#.#.#####v###.#.###.#.###v#.#.#.###.#.#.#.#.#.#.#.###.#.###v#######.#######.#######.#.#.#########################
#.....#...#...#...#...#...#.#.#.#...>.>...#.#...#...>.>.#.#...#.#.#.#.#.#.#.#...#.#.#...#.....#...#.....#.....#.#.#.........#.........#.....#
#.#########.#.#####.#.###.#.#.#.#.###v#####.#.#######v###.###.#.#.#.#.#.#.#.###.#.#.#.###.###.###.#.#####.###.#.#.#########.#.#######.#.###.#
#.....#.....#.....#.#...#.#.#.#.#...#...###...###...#...#...#.#.#.#.#.#.#.#.#...#...#...#...#.....#.......#...#.#...#...###.#.#.......#...#.#
#####.#.#########.#.###.#.#.#.#.###.###.#########.#.###.###.#.#.#.#.#.#.#.#.#.#########.###.###############.###.###.#.#.###.#.#.#########.#.#
#.....#.#.........#...#.#.#.#.#.#...###.......#...#.#...###.#.#.#.#.#.#.#.#.#.#...#.....###.........#.......#...#...#.#...#...#...#.......#.#
#.#####.#.###########.#.#.#.#.#.#.###########.#.###.#.#####.#.#.#.#.#.#.#.#.#.#.#.#.###############.#.#######.###.###.###.#######.#.#######.#
#...#...#.........#...#.#.#.#.#...#...........#...#...#...#.#.#.#.#.#.#...#.#.#.#.#.....#####.......#...#...#...#.###.#...#.....#...#...#...#
###.#.###########.#.###.#.#.#.#####.#############.#####.#.#.#.#.#.#.#.#####.#.#.#.#####.#####.#########v#.#.###.#.###.#.###v###.#####.#.#.###
###...#...###...#.#...#...#...###...#...#.......#.......#.#...#.#.#.#...#...#.#.#.......#.....#.......>.>.#.#...#...#.#...>.###.......#...###
#######.#.###.#.#v###.###########.###.#.#.#####.#########.#####.#.#.###.#.###.#.#########.#####.#######v###.#.#####.#.#####v#################
#.......#.....#.#.>.#.......#...#.....#...#.....#.........#...#...#.#...#.#...#...#...###.#...#.....###...#.#.....#.#...#...###...#...#.....#
#.#############.#v#.#######.#.#.###########.#####.#########.#.#####.#.###.#.#####.#.#.###.#.#.#####.#####.#.#####.#.###.#.#####.#.#.#.#.###.#
#.............#...#.......#.#.#...........#...###.......#...#...###...###.#...###...#...#...#.#.....#...#.#.#...#.#.#...#.#...#.#...#.#.#...#
#############.###########.#.#.###########.###.#########.#.#####.#########.###.#########.#####.#.#####.#.#.#.#.#.#.#.#.###.#.#.#.#####.#.#.###
#...#...#...#...........#.#.#...#.......#.....#...###...#.#.....#...#...#.#...#.........#...#.#.#.....#...#.#.#...#.#...#.#.#.#.#.....#.#...#
#.#.#.#.#.#.###########.#.#.###.#.#####.#######.#.###.###.#.#####.#.#.#.#.#.###.#########.#.#.#.#.#########.#.#####.###.#.#.#.#.#.#####.###.#
#.#...#...#.......#.....#...###...#...#...#.....#.#...###.#.#...#.#...#.#...###...........#.#.#.#.....#...#.#...#...#...#...#.#.#.#...#.#...#
#.###############.#.###############.#.###.#.#####.#.#####.#.#.#.#.#####.###################.#.#.#####.#.#.#.###.#.###.#######.#.#.#.#.#.#.###
#...............#.#.......#...#.....#.....#.#.....#.......#.#.#.#...#...###.................#...#...#...#.#.#...#...#.....#...#.#.#.#...#...#
###############.#.#######.#.#.#.###########.#.#############.#.#.###.#.#####.#####################.#.#####.#.#.#####.#####.#.###.#.#.#######.#
#...............#.#.....#...#.#.............#.....#.......#.#.#.###.#.#...#.......#...........#...#.....#.#...#.....#.....#.....#...###.....#
#.###############.#.###.#####.###################.#.#####.#.#.#.###.#.#.#.#######.#.#########.#.#######.#.#####.#####.#################.#####
#.......#...#...#...###.......###...#.............#.....#...#.#...#.#...#.###...#...#.........#.......#...#...#.......###...#...#.......#...#
#######.#.#.#.#.#################.#.#.#################.#####.###.#.#####.###.#.#####.###############.#####.#.###########.#.#.#.#.#######.#.#
#...###...#...#.....#...#...#.....#.#.........#...#.....#...#.#...#.#.....#...#.......###...###...###...#...#...#...#.....#.#.#.#.....#...#.#
#.#.###############.#.#.#.#.#.#####.#########.#.#.#.#####.#.#.#.###.#.#####.#############.#.###.#.#####.#.#####.#.#.#.#####.#.#.#####.#.###.#
#.#.................#.#.#.#.#.#.....#.........#.#.#...###.#.#.#.#...#.#...#.......#.....#.#.#...#.......#.#.....#.#.#.#.....#.#...###...#...#
#.###################.#.#.#.#.#.#####.#########.#.###.###.#.#.#.#.###.#.#.#######.#.###.#.#.#.###########.#.#####.#.#.#.#####.###.#######.###
#.#...#...#.....#...#.#.#.#.#.#.#...#.......#...#...#...#.#.#.#.#...#.#.#.###...#...#...#.#.#.....#.......#.....#.#.#.#.....#...#.#.....#...#
#.#.#.#.#.#.###.#.#.#.#.#.#.#.#.#.#.#######.#.#####.###.#.#.#.#.###.#.#.#.###.#.#####v###.#.#####.#.###########.#.#.#.#####.###.#.#.###.###.#
#...#...#.#.#...#.#.#.#.#.#.#.#.#.#.###.....#...#...#...#.#.#.#...#.#.#.#...#.#.#...>.>.#.#.#...#...#...........#.#.#.#.....###.#.#.#...#...#
#########.#.#.###.#.#.#.#.#.#.#.#.#.###v#######.#.###v###.#.#.###.#.#.#.###.#.#.#.#####.#.#.#.#.#####v###########.#.#.#.#######.#.#.#.###v###
#.........#.#...#.#...#.#.#.#.#.#.#...>.>...#...#.#.>.>.#.#.#...#.#.#.#...#...#.#...###.#.#...#.#...>.>.#...#...#.#.#.#.#...#...#...#.#.>.###
#.#########.###.#.#####.#.#.#.#.#.#########.#.###.#.###.#.#.###.#.#.#.###.#####.###.###.#.#####.#.#####.#.#.#.#.#.#.#.#.#.#.#.#######.#.#v###
#.....#...#.#...#.#.....#.#.#.#.#.#.........#...#.#...#.#.#.#...#.#.#.#...#.....#...#...#.....#.#...#...#.#.#.#.#.#.#.#.#.#.#.#.......#.#.###
#####.#.#.#.#.###.#.#####.#.#.#.#.#.###########.#.###.#.#.#.#.###.#.#.#.###.#####.###.#######.#.###.#.###.#.#.#.#.#.#.#.#.#.#.#.#######.#.###
#####...#...#.....#.......#...#...#.............#.....#...#...###...#...###.......###.........#.....#.....#...#...#...#...#...#.........#...#
###########################################################################################################################################.#'''

inp_s = '''\
#.#####################
#.......#########...###
#######.#########.#.###
###.....#.>.>.###.#.###
###v#####.#v#.###.#.###
###.>...#.#.#.....#...#
###v###.#.#.#########.#
###...#.#.#.......#...#
#####.#.#.#######.#.###
#.....#.#.#.......#...#
#.#####.#.#.#########v#
#.#...#...#...###...>.#
#.#.#v#######v###.###v#
#...#.>.#...>.>.#.###.#
#####v#.#.###v#.#.###.#
#.....#...#...#.#.#...#
#.#########.###.#.#.###
#...###...#...#...#.###
###.###.#.###v#####v###
#...#...#.#.>.>.#.>.###
#.###.###.#.###.#.#v###
#.....###...###...#...#
#####################.#'''

sam = 0
# sam = 0x0000000000000001
inp = inp_s if sam else inp_o

sys.setrecursionlimit(10**9)

g = [list(l) for l in inp.splitlines()]
h = len(g)
w = len(g[0])

sy, sx = next((0, x) for x in range(w) if g[0][x] == '.')
ey, ex = next((h - 1, x) for x in range(w) if g[-1][x] == '.')

D = ((0, 1), (1, 0), (0, -1), (-1, 0))

cp = {}

for y in range(h):
    for x in range(w):
        if g[y][x] == '#':
            continue
        nxt = set()
        for dy, dx in D:
            ny = y + dy
            nx = x + dx
            if ny < 0 or ny >= h or nx < 0 or nx >= w or g[ny][nx] == '#':
                continue
            nxt.add((ny, nx))
        if len(nxt) > 2:
            cp[y, x] = len(nxt)

# print(h, w, h * w)
# print(cp, len(cp))

dist = defaultdict(dict)


def calc_dist(ay, ax, by, bx):
    ans = 0
    seen = set()

    def dfs(y, x):
        nonlocal ans
        if y < 0 or y >= h or x < 0 or x >= w or g[y][x] == '#':
            return
        if (y, x) in seen:
            return
        if (y, x) == (by, bx):
            ans = max(ans, len(seen))
            return
        if (y, x) != (ay, ax) and (y, x) in cp:
            return
        seen.add((y, x))
        for dy, dx in D:
            ny = y + dy
            nx = x + dx
            dfs(ny, nx)
        seen.remove((y, x))

    dfs(ay, ax)
    return ans


cp = [(sy, sx)] + list(cp.keys()) + [(ey, ex)]
for i in range(len(cp)):
    for j in range(len(cp)):
        if i == j:
            continue
        a = calc_dist(*cp[i], *cp[j])
        if a:
            dist[i][j] = a

# print(dist)

ans = 0


def dfs2(i, seen, d):
    global ans
    if seen >> i & 1:
        return
    if i == len(cp) - 1:
        ans = max(ans, d)
        return
    seen |= 1 << i
    for j, x in dist[i].items():
        dfs2(j, seen, d + x)


dfs2(0, 0, 0)
print(ans)
