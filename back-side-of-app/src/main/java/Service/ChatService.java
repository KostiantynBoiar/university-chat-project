package Service;


import org.springframework.stereotype.Service;

@Service
public class ChatService {

    public String encryptedMessage(String data){

        String encryptedMessageAsString = data;
        return encryptedMessageAsString;
    }
     public String decryptedMessage(String encryptedData){ return encryptedData; }

}
