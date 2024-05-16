// Copyright Big Woof Studios, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TangiClientTarget : TargetRules
{
	public TangiClientTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Client;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;

		ExtraModuleNames.AddRange( new string[] { "Tangi" } );
	}
}