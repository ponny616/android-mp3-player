
package com.samples.servicelauncher;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class ServiceLauncherActivity extends Activity {

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_service_launcher);

        final Button btnStart = (Button) findViewById(R.id.btn_start);
        final Button btnStop = (Button) findViewById(R.id.btn_stop);

        btnStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startService(new Intent(ServiceLauncherActivity.this, PlayService.class));
            }
        });
      
        btnStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                stopService(new Intent(ServiceLauncherActivity.this, PlayService.class));
            }
        });
     }
}