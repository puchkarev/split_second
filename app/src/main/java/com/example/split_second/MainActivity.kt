package com.example.split_second

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
// import com.example.split_second.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    // private lateinit var binding: ActivityMainBinding

    private lateinit var glView: GameGLSurfaceView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Initialize the GLSurfaceView
        glView = GameGLSurfaceView(this)
        setContentView(glView)

        /*
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()
         */
    }

    /**
     * A native method that is implemented by the 'split_second' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'split_second' library on application startup.
        init {
            System.loadLibrary("split_second")
        }

        @JvmStatic
        external fun initOpenGL()

        @JvmStatic
        external fun render()
    }
}