class CarimSingleton<Class T> {
    private static ref T instance;

    static T Get() {
        if (!instance) {
            Class.CastTo(instance, T.Spawn());
        }
        return instance;
    }
}
