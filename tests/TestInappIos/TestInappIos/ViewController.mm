//
//  ViewController.m
//  TestInappIos
//
//  Created by Florian on 19/01/15.
//  Copyright (c) 2015 CotC. All rights reserved.
//

#import "ViewController.h"
#import "CStoreManager.h"

@implementation ViewController

- (void)viewDidLoad {
	[super viewDidLoad];

	CHJSON setupJson;
	setupJson.Put("key", "cloudbuilder-key");
	setupJson.Put("secret", "azerty");
	setupJson.Put("env", "http://195.154.227.44:8000");
//	setupJson.Put("httpVerbose", true);
//	setupJson.Put("env", "https://sandbox-api[id].clanofthecloud.mobi");
	CClan::Instance()->Setup(&setupJson, MakeResultHandler([] (eErrorCode err, const CCloudResult *result) {
		NSLog(@"Setup: %s\n", cstring(result->Print(), true).c_str());
		
		CUserManager::Instance()->LoginAnonymous(MakeResultHandler([] (eErrorCode err, const CCloudResult *result) {
			NSLog(@"LoginAnonymous: %s\n", cstring(result->Print(), true).c_str());
		}));
	}));

	[NSThread detachNewThreadSelector:@selector(idleTask) toTarget:self withObject:nil];
}

- (void)doWork:(id)sender {
	owned_ref<CHJSON> config (CHJSON::parse("{\"transaction\": {\"gold\": 1}, \"description\": \"Just a test\"}"));
	CUserManager::Instance()->TransactionExtended(config, MakeResultHandler([] (eErrorCode err, const CCloudResult *result) {
		CUserManager::Instance()->Balance("private", MakeResultHandler([] (eErrorCode err, const CCloudResult *result) {
			NSLog(@"Result from balance: %s\n", cstring(result->Print(), true).c_str());
			
			CStoreManager::Instance()->FetchProductInformation(MakeResultHandler([] (eErrorCode err, const CCloudResult *result) {
				NSLog(@"Result from product information: %s\n", cstring(result->Print(), true).c_str());
				
				CHJSON config;
				config.Put("productId", "smallpurse");
				CStoreManager::Instance()->LaunchPurchase(MakeResultHandler([] (eErrorCode err, const CCloudResult *result) {
					NSLog(@"Result from purchase: %s\n", cstring(result->Print(), true).c_str());
				}), &config);
			}), CHJSON::Empty());
		}));
	}));
}

- (void)popNextCallback {
	CClan::Instance()->ProcessIdleTasks();
}

- (void)idleTask {
	while (true) {
		usleep(100000);
		[self performSelectorOnMainThread:@selector(popNextCallback) withObject:self waitUntilDone:YES];
	}
}

@end
