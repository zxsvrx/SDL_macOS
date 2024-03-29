/*
	Copyright (c) 2024 zxsvrx
	
	This software is provided ‘as-is’, without any express or implied
	warranty. In no event will the authors be held liable for any damages
	arising from the use of this software.
	
	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:
	
	1. The origin of this software must not be misrepresented; you must not
	claim that you wrote the original software. If you use this software
	in a product, an acknowledgment in the product documentation would be
	appreciated but is not required.
	
	2. Altered source versions must be plainly marked as such, and must not be
	misrepresented as being the original software.
	
	3. This notice may not be removed or altered from any source
	distribution.
*/

#include "SDLM_Timer.h"

#import <Cocoa/Cocoa.h>

int SDLM_Timer_StartRunLoopTimer(SDLM_Timer *timer, void (*callback)()) {
	if (timer == NULL) {
		return -1;
	}

	if (callback == NULL) {
		return -2;
	}
	
	@autoreleasepool {		
		NSTimer *nstimer = [NSTimer scheduledTimerWithTimeInterval:timer->time
        	                                   				repeats:(BOOL)timer->repeat
        	                                   				block:^(NSTimer *unusedTimer) {
        	                                   					callback();
        	                                   				}];
		
		[[NSRunLoop currentRunLoop] addTimer:nstimer forMode:NSRunLoopCommonModes];
		
		timer->data = (__bridge void*) nstimer;
	}

	return 0;
}

int SDLM_Timer_InvalidateTimer(SDLM_Timer *timer) {
	if (timer == NULL) {
		return -1;
	}

	if (timer->data == NULL) {
		return -2;
	}
	
	@autoreleasepool {
		NSTimer *nstimer = (__bridge NSTimer*)timer->data;

		[nstimer invalidate];
		nstimer = nil;

		timer->data = NULL;
	}

	return 0;
}
