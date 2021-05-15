// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;
using System.IO;

public class PlayFabParty : ModuleRules
{
    public PlayFabParty(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = true;
        bUseUnity = true;
        
        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "Projects"
            }
        );

        string BaseDirectory = System.IO.Path.GetFullPath(System.IO.Path.Combine(ModuleDirectory, "..", ".."));
        string LibraryDirectory = System.IO.Path.Combine(BaseDirectory, "ThirdParty", Target.Platform.ToString());

     
        bool bHasPlayFabPartyCpp = System.IO.Directory.Exists(LibraryDirectory);
        if (bHasPlayFabPartyCpp && Target.Type != TargetRules.TargetType.Server)
        {
            if (Target.Platform == UnrealTargetPlatform.Win64)
            {
                PublicDefinitions.Add("PARTY_WINDOWS=1");
                PublicDefinitions.Add("WITH_PLAYFAB_PARTY=1");                

                var AdditionalDLLNames = new List<string>() { "PartyWin.dll" };

                foreach (var DLLName in AdditionalDLLNames)
                {
                    string SDKLibWindows = System.IO.Path.Combine(LibraryDirectory, DLLName);
                    RuntimeDependencies.Add(SDKLibWindows);
                }

                var PublicDelayLoadDLLNames = new List<string>() { "PartyWin.dll" };
                foreach (var DLLName in PublicDelayLoadDLLNames)
                {
                    PublicDelayLoadDLLs.Add(DLLName);
                }
            }
            else if (Target.Platform == UnrealTargetPlatform.Android)
            {
                PublicDefinitions.Add("WITH_PLAYFAB_PARTY=1");                
                PublicDefinitions.Add("PARTY_WINDOWS=0");
                
                // var AdditionalDLLNames = new List<string>() { "libparty.so" };
                //
                // foreach (var DLLName in AdditionalDLLNames)
                // {
                //     string SDKLibWindows = System.IO.Path.Combine(LibraryDirectory, DLLName);
                //     RuntimeDependencies.Add(SDKLibWindows);
                // }
                //
                // var PublicDelayLoadDLLNames = new List<string>() { "libparty.so" };
                // foreach (var DLLName in PublicDelayLoadDLLNames)
                // {
                //     PublicDelayLoadDLLs.Add(DLLName);
                // }

                // var Path = System.IO.Path.Combine(LibraryDirectory, "lib", "libcppsdk.a");
                var PluginPath = Utils.MakePathRelativeTo(ModuleDirectory, Target.RelativeEnginePath);
                AdditionalPropertiesForReceipt.Add("AndroidPlugin", System.IO.Path.Combine(PluginPath, "PlayFabParty_APL.xml"));

                var Path = System.IO.Path.Combine(LibraryDirectory, "libparty.so");

                //PublicLibraryPaths.Add(Path);
                PublicAdditionalLibraries.Add(Path);
                System.Console.WriteLine("PlayFabParty.Build:  path " + Path);
                System.Console.WriteLine("PlayFabParty.Build: PublicAdditionalLibraries: " + string.Join(";", PublicAdditionalLibraries));
            }
            else
            {
                PublicDefinitions.Add("WITH_PLAYFAB_PARTY=0");
                PublicDefinitions.Add("PARTY_WINDOWS=0");
            }
        }
        else
        {
            PublicDefinitions.Add("WITH_PLAYFAB_PARTY=0");
            PublicDefinitions.Add("PARTY_WINDOWS=0");
        }
    }
}
