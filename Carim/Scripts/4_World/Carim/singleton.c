#ifndef CarimSingleton
#define CarimSingleton

class CarimSingleton<Class T> {
    private static ref T instance;

    static T Get() {
        if (!instance) {
            CarimLogging.Trace("Spawn " + T.ToString());
            Class.CastTo(instance, T.Spawn());
        }
        return instance;
    }
}

#endif
