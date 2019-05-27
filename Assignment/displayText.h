//
//  displayText.h
//  Assignment
//
//  Created by Josef Bode on 5/26/19.
//  Copyright © 2019 CodeBound. All rights reserved.
//

#ifndef displayText_h
#define displayText_h

#include <stdio.h>

#include "graphics.h"

//prototypes
void init_display_text(GameState *game);
void draw_display_text(GameState *game);
void changeScenario(GameState *game);
void shutdown_display_text(GameState *game);

#endif /* displayText_h */
