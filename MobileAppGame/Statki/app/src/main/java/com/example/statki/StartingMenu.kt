package com.example.statki

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View

class StartingMenu : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_starting_menu)
    }

    // Go to Host Activity
    fun goNewGame(view: View) {
        startActivity(Intent(this, Host::class.java))
    }

}
