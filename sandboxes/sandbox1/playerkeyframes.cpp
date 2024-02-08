#include "playerkeyframes.h"

PlayerKeyframes::PlayerKeyframes() : Keyframes(4,2){
	for (int y = 1; y >= 0; y--) {
		for (int x = 0; x < 4; x++) {
			frames.push_back(
				{
					x * w  , y * h,      //left-bottom
					x * w+w, y * h,      //right-bottom
					x * w+w, y * h+h,    //right-top
					x * w  , y * h,      //left-bottom
					x * w+w, y * h+h,    //right-top
					x * w  , y * h+h     //left-top
				}
			);
		};
	}

}
