// Copyright Big Woof Studios, LLC. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TangiEditorTarget : TargetRules
{
	public TangiEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_4;

		ExtraModuleNames.AddRange( new string[] { "Tangi" } );
	}
}
