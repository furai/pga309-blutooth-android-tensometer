package pl.furai.pga309;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;
import android.util.Log;


public class MainActivity extends Activity {

    private static final int REQUEST_ENABLE_BT = 1337;
    private static final boolean D = true;
    private static final String TAG = MainActivity.class.getSimpleName();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mBluetoothAdapter == null) {
            Toast.makeText(getApplicationContext(), "Device does not support Bluetooth.", Toast.LENGTH_LONG).show();
            if (D) Log.d(TAG, "Device does not support Bluetooth.");
        } else {
            Toast.makeText(getApplicationContext(), "Device supports Bluetooth.", Toast.LENGTH_LONG).show();
            if (D) Log.d(TAG, "Device supports Bluetooth.");
        }
        //Enable bluetooth if it's disabled
        if (!mBluetoothAdapter.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }
        
    }


    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            Toast.makeText(getApplicationContext(), "Lucas was too lazy to implement settings.", Toast.LENGTH_SHORT).show();
            if (D) Log.d(TAG, "Lucas was too lazy to implement settings.");
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
