package org.lineageos.settings;

import android.content.res.ColorStateList;
import android.os.Bundle;
import android.preference.PreferenceActivity;

public class MonetPreferenceActivity extends PreferenceActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        int monetBackground = getColor(android.R.color.monet_background_device_default);
        getWindow().getDecorView().setBackgroundColor(monetBackground);
        getWindow().getDecorView().setBackgroundTintList(ColorStateList.valueOf(monetBackground));
    }
}
