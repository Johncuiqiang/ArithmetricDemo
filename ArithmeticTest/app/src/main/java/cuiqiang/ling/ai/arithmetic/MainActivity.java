package cuiqiang.ling.ai.arithmetic;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    private View mBtnTest;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
        initData();
    }

    private void initView() {
        mBtnTest = findViewById(R.id.btn_test);
    }

    private void initData() {
        mBtnTest.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String str = getStr();
                Log.d("1111","str"+str);
            }
        });
    }

    static {
        System.loadLibrary("ArithmeticLib");
    }

    public native String getStr();
}
