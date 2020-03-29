package com.example.statki;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class Client extends AppCompatActivity {

    EditText editTextAddress;
    Button buttonConnect, buttonReady;
    TextView textViewState, textViewRx;

    ClientHandler clientHandler;
    ClientThread clientThread;

    private static final int PORT = 8080;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();
        StrictMode.setThreadPolicy(policy);

        setContentView(R.layout.activity_client);
        editTextAddress = findViewById(R.id.address_text);
        buttonConnect = findViewById(R.id.connect_button);
        buttonReady = findViewById(R.id.ready_button);
        textViewState = findViewById(R.id.state_view);
        textViewRx = findViewById(R.id.received_text);

        buttonConnect.setOnClickListener(buttonConnectOnClickListener);
        buttonReady.setEnabled(false);
        clientHandler = new ClientHandler(this);
    }

    // Setting Listener on the buttonConnect
    View.OnClickListener buttonConnectOnClickListener =
    new View.OnClickListener() {

        @Override
        public void onClick(View arg0) {

            clientThread = new ClientThread(
                    editTextAddress.getText().toString(),
                    PORT,
                    clientHandler
            );
            clientThread.start();

            buttonConnect.setEnabled(false);
        }
    };

    private void updateState(String state){
        textViewState.setText(state);
    }

    private void updateRxMsg(String msg){
        textViewRx.append(msg + "\n");
    }

    private void clientEnd(){
        clientThread = null;
        textViewState.setText("clientEnd()");
        buttonConnect.setEnabled(true);

    }

    public static class ClientHandler extends Handler {
        public static final int UPDATE_STATE = 0;
        public static final int UPDATE_MSG = 1;
        public static final int UPDATE_END = 2;
        private Client parent;

        public ClientHandler(Client parent) {
            super();
            this.parent = parent;
        }

        @Override
        public void handleMessage(Message msg) {

            switch (msg.what){
                case UPDATE_STATE:
                parent.updateState((String)msg.obj);
                break;
                case UPDATE_MSG:
                parent.updateRxMsg((String)msg.obj);
                break;
                case UPDATE_END:
                parent.clientEnd();
                break;
                default:
                super.handleMessage(msg);
            }

        }

    }
}
