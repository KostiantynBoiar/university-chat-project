package com.example.weekofscienceproject2023.Wrapper;

public class CRSAWrapper {
    static {
        System.loadLibrary("/home/kostiantyn/IdeaProjects/university-chat-project/CRSA/RSADLL");
    }
    public native void rsaEncrypt(int publicKey, byte[] plainText, int plainTextLength,
                                  byte[][] encryptedText, int[] encryptedTextLength);
    public native void rsaDecrypt(int privateKey, byte[] encryptedText, int encryptedTextLength,
                                  byte[][] decryptedText, int[] decryptedTextLength);
}
