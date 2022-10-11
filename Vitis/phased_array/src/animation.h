const double knot_animation[198][3] = {
	{4.190000057220459, 0.0, 0.0},
	{4.159215927124023, 0.39619413018226624, 0.2271992415189743},
	{4.043683052062988, 0.7793560028076172, 0.44932815432548523},
	{3.873904228210449, 1.134655475616455, 0.6591219902038574},
	{3.6295371055603027, 1.453047513961792, 0.853787362575531},
	{3.3507542610168457, 1.7229385375976562, 1.0258082151412964},
	{3.0161311626434326, 1.938349723815918, 1.1729893684387207},
	{2.6736905574798584, 2.096778154373169, 1.2908391952514648},
	{2.2997121810913086, 2.1927711963653564, 1.3750591278076172},
	{1.94380784034729, 2.2365527153015137, 1.4276458024978638},
	{1.5819039344787598, 2.221473217010498, 1.4398187398910522},
	{1.2565603256225586, 2.16931414604187, 1.4221071004867554},
	{0.9467400312423706, 2.0730714797973633, 1.360801100730896},
	{0.6808074712753296, 1.9598170518875122, 1.2741453647613525},
	{0.4427369236946106, 1.824986457824707, 1.1458970308303833},
	{0.24460749328136444, 1.692491888999939, 0.9981621503829956},
	{0.07441363483667374, 1.5621343851089478, 0.8165661692619324},
	{-0.06850945204496384, 1.4484539031982422, 0.6218530535697937},
	{-0.19473369419574738, 1.3544025421142578, 0.4056948721408844},
	{-0.3113172650337219, 1.2836891412734985, 0.18317458033561707},
	{-0.4286961555480957, 1.2386362552642822, -0.04568822309374809},
	{-0.5549062490463257, 1.2146992683410645, -0.2738380432128906},
	{-0.6984213590621948, 1.2097012996673584, -0.49250897765159607},
	{-0.8660933375358582, 1.2152111530303955, -0.7034346461296082},
	{-1.059619426727295, 1.2228659391403198, -0.8901488780975342},
	{-1.286123275756836, 1.2243093252182007, -1.0624430179595947},
	{-1.5346548557281494, 1.206865906715393, -1.198900580406189},
	{-1.8160573244094849, 1.1640009880065918, -1.3146448135375977},
	{-2.103231430053711, 1.0842912197113037, -1.3879326581954956},
	{-2.413069009780884, 0.9619917273521423, -1.4348158836364746},
	{-2.704348087310791, 0.7940682768821716, -1.4383689165115356},
	{-2.9989640712738037, 0.5734220743179321, -1.4114153385162354},
	{-3.2491369247436523, 0.3102549612522125, -1.3451728820800781},
	{-3.47825288772583, -0.004530608654022217, -1.2474064826965332},
	{-3.641432046890259, -0.3477146029472351, -1.1176508665084839},
	{-3.760695695877075, -0.728672981262207, -0.959559977054596},
	{-3.8009402751922607, -1.1160567998886108, -0.7785227298736572},
	{-3.7829248905181885, -1.5170279741287231, -0.5766543745994568},
	{-3.683197259902954, -1.898820161819458, -0.36165308952331543},
	{-3.5241684913635254, -2.2655322551727295, -0.13668301701545715},
	{-3.29128360748291, -2.58829402923584, 0.09133043885231018},
	{-3.012251615524292, -2.870335102081299, 0.31680935621261597},
	{-2.6763174533843994, -3.088634967803955, 0.535193920135498},
	{-2.318272829055786, -3.2503623962402344, 0.7389594316482544},
	{-1.9265519380569458, -3.336885929107666, 0.9256141185760498},
	{-1.5411725044250488, -3.3646481037139893, 1.0879582166671753},
	{-1.1477484703063965, -3.3162012100219727, 1.2236045598983765},
	{-0.7859631180763245, -3.2202248573303223, 1.329102635383606},
	{-0.43968066573143005, -3.058046340942383, 1.3994085788726807},
	{-0.14093878865242004, -2.8687744140625, 1.4381369352340698},
	{0.1254202276468277, -2.632894515991211, 1.4354708194732666},
	{0.34069502353668213, -2.3930070400238037, 1.4036542177200317},
	{0.5171756744384766, -2.1318271160125732, 1.3281900882720947},
	{0.6505066752433777, -1.886023998260498, 1.2284815311431885},
	{0.7506551742553711, -1.6437054872512817, 1.088279366493225},
	{0.8234230279922485, -1.4283405542373657, 0.9298349022865295},
	{0.8784984946250916, -1.2336784601211548, 0.7396954298019409},
	{0.9251300692558289, -1.068245530128479, 0.5377572774887085},
	{0.9736981391906738, -0.928419291973114, 0.3172471523284912},
	{1.0313888788223267, -0.8111546635627747, 0.09177234768867493},
	{1.107527494430542, -0.7117646932601929, -0.13688069581985474},
	{1.2051208019256592, -0.6210340857505798, -0.3633967339992523},
	{1.3283123970031738, -0.5317760705947876, -0.5773399472236633},
	{1.4774094820022583, -0.4330325126647949, -0.782170295715332},
	{1.6465169191360474, -0.3173401355743408, -0.9601473212242126},
	{1.8370416164398193, -0.17374151945114136, -1.1224157810211182},
	{2.0299999713897705, 1.3057956264870044e-15, -1.2470765113830566},
	{2.231410503387451, 0.21594591438770294, -1.349818468093872},
	{2.4107120037078857, 0.46462664008140564, -1.4094754457473755},
	{2.5790963172912598, 0.7614147663116455, -1.441734790802002},
	{2.701185941696167, 1.08139169216156, -1.4311273097991943},
	{2.7907605171203613, 1.4438742399215698, -1.3895158767700195},
	{2.816683053970337, 1.8101723194122314, -1.3098700046539307},
	{2.792280912399292, 2.201525926589966, -1.1989812850952148},
	{2.6973955631256104, 2.5719614028930664, -1.057811975479126},
	{2.5441880226135254, 2.941577672958374, -0.8894795775413513},
	{2.3250670433044434, 3.2650997638702393, -0.7001232504844666},
	{2.053018569946289, 3.560033082962036, -0.4918862581253052},
	{1.7297786474227905, 3.787687063217163, -0.2725217938423157},
	{1.3719748258590698, 3.964651346206665, -0.045621663331985474},
	{0.985098659992218, 4.06063175201416, 0.1822931319475174},
	{0.5905758142471313, 4.09561824798584, 0.40515583753585815},
	{0.19271695613861084, 4.045626640319824, 0.6189046502113342},
	{-0.18433156609535217, 3.9388668537139893, 0.8158478140830994},
	{-0.5396830439567566, 3.7535781860351562, 0.9937137365341187},
	{-0.8516173362731934, 3.528754234313965, 1.145760178565979},
	{-1.1218661069869995, 3.2414193153381348, 1.2692928314208984},
	{-1.3373603820800781, 2.9394941329956055, 1.3620402812957764},
	{-1.5000267028808594, 2.5981223583221436, 1.4181231260299683},
	{-1.6096339225769043, 2.2675318717956543, 1.4428414106369019},
	{-1.6666642427444458, 1.9234330654144287, 1.4253427982330322},
	{-1.6831767559051514, 1.6091886758804321, 1.3795270919799805},
	{-1.6589996814727783, 1.3046518564224243, 1.2902309894561768},
	{-1.6128898859024048, 1.0387921333312988, 1.1778368949890137},
	{-1.5464636087417603, 0.7972574234008789, 1.0262795686721802},
	{-1.4774209260940552, 0.5924345850944519, 0.8577396869659424},
	{-1.410528540611267, 0.4141685664653778, 0.6598461866378784},
	{-1.3566423654556274, 0.2617737948894501, 0.4514886438846588},
	{-1.3220744132995605, 0.12624280154705048, 0.22752200067043304},
	{-1.3092281818389893, 0.0, 1.4901161193847656e-08},
	{-1.3220744132995605, -0.12624280154705048, -0.22752200067043304},
	{-1.3566423654556274, -0.26177382469177246, -0.4514886736869812},
	{-1.410528540611267, -0.4141685664653778, -0.6598461866378784},
	{-1.4774209260940552, -0.5924345850944519, -0.8577396869659424},
	{-1.5464636087417603, -0.7972574234008789, -1.0262795686721802},
	{-1.6128898859024048, -1.0387921333312988, -1.1778368949890137},
	{-1.6589996814727783, -1.3046518564224243, -1.2902309894561768},
	{-1.6831767559051514, -1.6091886758804321, -1.3795270919799805},
	{-1.6666642427444458, -1.9234330654144287, -1.4253427982330322},
	{-1.6096339225769043, -2.2675318717956543, -1.4428414106369019},
	{-1.5000267028808594, -2.5981223583221436, -1.4181231260299683},
	{-1.3373603820800781, -2.9394941329956055, -1.3620402812957764},
	{-1.1218661069869995, -3.2414193153381348, -1.2692928314208984},
	{-0.8516172766685486, -3.528754234313965, -1.145760178565979},
	{-0.5396830439567566, -3.7535781860351562, -0.9937137365341187},
	{-0.18433153629302979, -3.9388668537139893, -0.8158478140830994},
	{0.19271695613861084, -4.045626640319824, -0.6189046502113342},
	{0.5905758142471313, -4.09561824798584, -0.40515583753585815},
	{0.985098659992218, -4.06063175201416, -0.1822931319475174},
	{1.3719747066497803, -3.964651107788086, 0.04562164843082428},
	{1.7297786474227905, -3.787687063217163, 0.2725217938423157},
	{2.053018569946289, -3.560033082962036, 0.4918862581253052},
	{2.3250670433044434, -3.2650997638702393, 0.7001232504844666},
	{2.5441880226135254, -2.941577672958374, 0.8894796371459961},
	{2.6973955631256104, -2.5719614028930664, 1.057811975479126},
	{2.792280912399292, -2.201525926589966, 1.1989812850952148},
	{2.816683053970337, -1.8101723194122314, 1.3098700046539307},
	{2.7907605171203613, -1.4438742399215698, 1.3895158767700195},
	{2.701185941696167, -1.08139169216156, 1.4311273097991943},
	{2.5790963172912598, -0.7614147067070007, 1.441734790802002},
	{2.4107120037078857, -0.46462664008140564, 1.4094754457473755},
	{2.231410503387451, -0.21594591438770294, 1.349818468093872},
	{2.0299999713897705, 2.611591252974009e-15, 1.2470765113830566},
	{1.8370416164398193, 0.17374151945114136, 1.1224157810211182},
	{1.6465169191360474, 0.3173401355743408, 0.9601473212242126},
	{1.4774094820022583, 0.4330325126647949, 0.782170295715332},
	{1.3283123970031738, 0.5317760705947876, 0.5773399472236633},
	{1.2051208019256592, 0.6210340857505798, 0.3633967339992523},
	{1.107527494430542, 0.7117646932601929, 0.13688069581985474},
	{1.0313888788223267, 0.8111546635627747, -0.09177234768867493},
	{0.9736981391906738, 0.928419291973114, -0.3172471523284912},
	{0.9251300692558289, 1.068245530128479, -0.5377572774887085},
	{0.8784984946250916, 1.2336784601211548, -0.7396954298019409},
	{0.8234230279922485, 1.4283405542373657, -0.9298349022865295},
	{0.7506551742553711, 1.6437054872512817, -1.088279366493225},
	{0.6505066752433777, 1.886023998260498, -1.2284815311431885},
	{0.5171756744384766, 2.1318271160125732, -1.3281900882720947},
	{0.34069502353668213, 2.3930070400238037, -1.4036542177200317},
	{0.1254202276468277, 2.632894515991211, -1.4354708194732666},
	{-0.14093880355358124, 2.8687744140625, -1.4381369352340698},
	{-0.43968066573143005, 3.058046340942383, -1.3994085788726807},
	{-0.7859631776809692, 3.2202248573303223, -1.329102635383606},
	{-1.1477484703063965, 3.3162012100219727, -1.2236045598983765},
	{-1.5411725044250488, 3.3646481037139893, -1.0879582166671753},
	{-1.9265519380569458, 3.336885929107666, -0.9256141185760498},
	{-2.318272829055786, 3.2503623962402344, -0.7389594316482544},
	{-2.6763174533843994, 3.088634967803955, -0.535193920135498},
	{-3.012251615524292, 2.870335102081299, -0.31680935621261597},
	{-3.29128360748291, 2.58829402923584, -0.09133043885231018},
	{-3.5241684913635254, 2.2655322551727295, 0.13668301701545715},
	{-3.683197259902954, 1.898820161819458, 0.36165308952331543},
	{-3.7829248905181885, 1.5170279741287231, 0.5766543745994568},
	{-3.8009402751922607, 1.1160567998886108, 0.7785227298736572},
	{-3.760695695877075, 0.728672981262207, 0.959559977054596},
	{-3.641432046890259, 0.3477146029472351, 1.1176508665084839},
	{-3.47825288772583, 0.004530608654022217, 1.2474064826965332},
	{-3.2491369247436523, -0.3102549612522125, 1.3451728820800781},
	{-2.9989640712738037, -0.5734220743179321, 1.4114153385162354},
	{-2.704348087310791, -0.7940682768821716, 1.4383689165115356},
	{-2.413069009780884, -0.9619916677474976, 1.4348158836364746},
	{-2.103231430053711, -1.0842912197113037, 1.3879326581954956},
	{-1.8160573244094849, -1.1640009880065918, 1.3146448135375977},
	{-1.5346548557281494, -1.206865906715393, 1.198900580406189},
	{-1.286123275756836, -1.2243093252182007, 1.0624430179595947},
	{-1.059619426727295, -1.2228659391403198, 0.8901488780975342},
	{-0.8660933375358582, -1.2152111530303955, 0.7034345865249634},
	{-0.6984213590621948, -1.2097012996673584, 0.49250897765159607},
	{-0.5549062490463257, -1.2146992683410645, 0.2738380432128906},
	{-0.4286961555480957, -1.2386362552642822, 0.04568822309374809},
	{-0.3113172948360443, -1.2836891412734985, -0.18317459523677826},
	{-0.19473369419574738, -1.3544025421142578, -0.4056948721408844},
	{-0.06850947439670563, -1.4484539031982422, -0.6218529939651489},
	{0.07441363483667374, -1.5621343851089478, -0.8165661692619324},
	{0.24460750818252563, -1.692491888999939, -0.9981622099876404},
	{0.4427369236946106, -1.824986457824707, -1.1458970308303833},
	{0.6808074712753296, -1.9598170518875122, -1.2741453647613525},
	{0.9467400312423706, -2.0730714797973633, -1.360801100730896},
	{1.2565603256225586, -2.16931414604187, -1.4221071004867554},
	{1.5819039344787598, -2.221473217010498, -1.4398187398910522},
	{1.94380784034729, -2.2365527153015137, -1.4276458024978638},
	{2.2997121810913086, -2.1927711963653564, -1.3750591278076172},
	{2.6736905574798584, -2.096778154373169, -1.2908391952514648},
	{3.0161311626434326, -1.938349723815918, -1.1729893684387207},
	{3.3507542610168457, -1.7229385375976562, -1.0258080959320068},
	{3.6295371055603027, -1.453047513961792, -0.853787362575531},
	{3.873904228210449, -1.134655475616455, -0.6591219305992126},
	{4.043683052062988, -0.7793560028076172, -0.44932815432548523},
	{4.159215927124023, -0.396194189786911, -0.2271992713212967}
};
