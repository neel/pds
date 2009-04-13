//
// C++ Interface: helper
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PDSHELPER_H
#define PDSHELPER_H

namespace PDS {

/**
	@author Neel Basu <neel.basu.z@gmail.com>
*/
class Helper{
	public:
		template <typename T>
		struct ConversibilityTo{
			static bool of(T& o){
				return true;
			}
			static bool of(...){
				return false;
			}
		};
	public:
    Helper();
    ~Helper();
};

}

#endif
