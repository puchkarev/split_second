An android game about a time traveler

# Setting up the environment.

1. Install AndroidStudio [https://developer.android.com/studio/install]

2. Clone the repository

```
git clone git@github.com:puchkarev/split_second
```

3. Import the submodules

```
cd split_second
git submodule init
git submodule update
```

4. Open the project located in split_second in Android Studio.
It will update/import the Gradle Files. First time this take a while.

5. It should be able to build and run.

# Game description

This is a 2d side scroller where you are traveling on a road with obstacles with some bushes oncoming cars and cars traveling the same direction.
The controls that you will have are just the ability to move left or right, and ability to drive faster or slower.
The goal is to complete as many stages as possible as quickly as possible.

When traveling closely behind another vehicle you can get a bit of a speed boost that will last for a short time.

The nuance of this specific version is that after you complete the first level, the second time around a new obstacle will be added, which is your previous
run, and this will also continue repeating for each following run. Note however since the same rules apply for all other preceding runs on the speed boost,
that means that if you end up driving in front of another (previous run) you will affect how they drive, and if that causes them to die you fail and will
have to retry this level.
