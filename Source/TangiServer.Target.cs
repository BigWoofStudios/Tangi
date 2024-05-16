// Copyright Big Woof Studios, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TangiServerTarget : TargetRules
{
	public TangiServerTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Server;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		bWithPushModel = true;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;

		ExtraModuleNames.AddRange( new string[] { "Tangi" } );
	}
}
