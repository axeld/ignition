/* Version numbers
 *
 * Copyright ©2005-2009 pinc Software. All Rights Reserved.
 * Licensed under the terms of the GNU General Public License, version 3.
 */
#ifndef VERSION_H
#define VERSION_H


#ifdef __amigaos4__
	#define VERSION "1.00 beta 2"
	#define INFODATE "21. Sep. 2014"
	#define IGNITION_COPYRIGHT "Copyright ©1996-2014 pinc Software."
	#define VERSTRING "$VER: ignitionOS4 " VERSION " (21.09.2014)"

	#define SCREEN_TITLE "ignitionOS4  V" VERSION "    "  IGNITION_COPYRIGHT
#else

	#define SCREEN_TITLE "ignition"

	#define VERSION "1.0 beta 1"
	#define INFODATE "24. Januar 2009"
	#define IGNITION_COPYRIGHT "Copyright ©1996-2009 pinc Software."
	#define VERSTRING "$VER: ignition " VERSION " (24.1.2009)"
#endif
#endif	/* VERSION_H */

