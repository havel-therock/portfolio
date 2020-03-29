package com.example.statki

import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.view.View

class Host : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_host)
    }

    // Go to Client Activity
    fun goClientActivity(view: View) {
        startActivity(Intent(this, Client::class.java))
    }

    // Go to Server Activity
    fun goServerActivity(view: View) {
        startActivity(Intent(this, Server::class.java))
    }
}
