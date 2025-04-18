class CarimDAL<Class T> {
    private static ref T instance;

    static string Path() {
        return "$profile:" + T.ToString() + ".json";
    }

    static void Save() {
        string error;
        if (!JsonFileLoader<T>.SaveFile(Path(), instance, error)) {
            CarimLogging.Warn("Settings save " + Path() + " " + error);
        }
    }

    static T Get() {
        if (!instance) {
            Class.CastTo(instance, T.Spawn());
            if (FileExist(Path())) {
                string error;
                if (!JsonFileLoader<T>.LoadFile(Path(), instance, error)) {
                    CarimLogging.Warn("Settings load " + Path() + " " + error);
                }
                instance.LoadDefaultsIfMissing();
            }
            Save();
        }
        return instance;
    }
}
