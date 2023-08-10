/* global Buffer */

/**
 * A number instance that can store numbers with virtually infinite size.
 */



export class BN {
  static get BN() {
    return BN;
  }

  static get default() {
    return BN;
  }

  static get defaults() {
    return { BN };
  }
}

declare global {
  function __createBN(): BN;
}
global.__createBN = () => {
  return new BN();
};

export default BN;
