import { NativeModules, Platform } from 'react-native';

interface NativeJSIStartSpec {
   helloworld: () => number;
}

// global func declaration for JSI functions
declare global {
  function nativeCallSyncHook(): unknown;
  var __JSIStartProxy: object | undefined;
}

// Check if the constructor exists. If not, try installing the JSI bindings.
if (global.__JSIStartProxy == null) {
  // Get the native JSIStart ReactModule
  const JSIStartModule = NativeModules.JSIStart;
  if (JSIStartModule == null) {
    let message =
      'Failed to install react-native-bignumber: The native `JSIStart` Module could not be found.';
    message +=
      '\n* Make sure react-native-bignumber is correctly autolinked (run `npx react-native config` to verify)';
    if (Platform.OS === 'ios' || Platform.OS === 'macos') {
      message += '\n* Make sure you ran `pod install` in the ios/ directory.';
    }
    if (Platform.OS === 'android') {
      message += '\n* Make sure gradle is synced.';
    }
    // check if Expo
    const ExpoConstants =
      NativeModules.NativeUnimoduleProxy?.modulesConstants?.ExponentConstants;
    if (ExpoConstants != null) {
      if (ExpoConstants.appOwnership === 'expo') {
        // We're running Expo Go
        throw new Error(
          'react-native-bignumber is not supported in Expo Go! Use EAS (`expo prebuild`) or eject to a bare workflow instead.'
        );
      } else {
        // We're running Expo bare / standalone
        message += '\n* Make sure you ran `expo prebuild`.';
      }
    }

    message += '\n* Make sure you rebuilt the app.';
    throw new Error(message);
  }

  // Check if we are running on-device (JSI)
  if (global.nativeCallSyncHook == null || JSIStartModule.install == null) {
    throw new Error(
      'Failed to install react-native-bignumber: React Native is not running on-device. JSIStart can only be used when synchronous method invocations (JSI) are possible. If you are using a remote debugger (e.g. Chrome), switch to an on-device debugger (e.g. Flipper) instead.'
    );
  }

  // Call the synchronous blocking install() function
  const result = JSIStartModule.install();
  if (result !== true)
    throw new Error(
      `Failed to install react-native-bignumber: The native JSIStart Module could not be installed! Looks like something went wrong when installing JSI bindings: ${result}`
    );

  // Check again if the constructor now exists. If not, throw an error.
  if (global.__JSIStartProxy == null)
    throw new Error(
      'Failed to install react-native-bignumber, the native initializer function does not exist. Are you trying to use JSIStart from different JS Runtimes?'
    );
}

// Hack alert! Object.assign doesn't work with jsi::HostObject out of the box
const proxy = global.__JSIStartProxy as any;
const native = {} as any;
Object.keys(proxy).forEach((key: string) => {
  console.log(proxy[key])
  native[key] = proxy[key];
});
export const NativeJSIStart = native as NativeJSIStartSpec;

