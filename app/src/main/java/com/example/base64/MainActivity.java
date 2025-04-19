package com.example.base64;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.example.base64.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'base64' library on application startup.
    static {
        Log.d("JNI", "Loading libyourlib.so");
        System.loadLibrary("base64");
        Log.d("JNI", "libyourlib.so loaded");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        EditText inputText = findViewById(R.id.inputText);
        TextView resultText = findViewById(R.id.resultText);
        Button encodeButton = findViewById(R.id.encodeButton);
        Button decodeButton = findViewById(R.id.decodeButton);

        // 点击“编码”按钮时触发 Base64 编码
        encodeButton.setOnClickListener(v -> {
            String input = inputText.getText().toString();
            String encoded = base64Encode(input);
            resultText.setText(encoded);
        });

        // 点击“解码”按钮时触发 Base64 解码
        decodeButton.setOnClickListener(v -> {
            String input = inputText.getText().toString();
            String decoded = base64Decode(input);



            resultText.setText(decoded);
        });

    }

    // JNI 方法声明
    public native String base64Encode(String input);
    public native String base64Decode(String input);

}