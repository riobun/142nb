//  ²Î¿¼£ºMultiplayer game programming, Joshua Glazer, Sanjay Madhav
//  ¸ü¸Ä£º¶ÅÃµ£¬ 2019.06.04

namespace StringUtils_dm
{
	string GetCommandLineArg( int inIndex );

	string Sprintf( const char* inFormat, ... );

	void	Log( const char* inFormat, ... );
}

#define LOG_SU( ... ) StringUtils_dm::Log( __VA_ARGS__ );