/*
HALOREACH.H
*/

#pragma once

/* ---------- macros */

#ifdef BLAMAPI
#	undef BLAMAPI
#endif

#ifdef HALOREACH_EXPORTS
#	define BLAMAPI __declspec(dllexport)
#else
#	define BLAMAPI __declspec(dllimport)
#endif
