class CarimRPCBase<Class T> extends Managed {
    static int GetType();
    static void Handle(PlayerIdentity sender, T params);

    static void OnRPC(PlayerIdentity sender, ParamsReadContext ctx) {
        CarimLogging.Trace("OnRPC " + T.ToString());
        T params;
        if (!ctx.Read(params)) {
            CarimLogging.Warn("Unable to read params from ctx");
            return;
        }
        if (GetGame().IsClient()) {
            HandleClient(sender, params);
        } else {
            HandleServer(sender, params);
        }
    }

    static void HandleClient(PlayerIdentity sender, T params) {
        Handle(sender, params);
    }

    static void HandleServer(PlayerIdentity sender, T params) {
        Handle(sender, params);
    }

    static void Send(Man player, T params, bool guaranteed, PlayerIdentity recipient = null) {
        CarimLogging.Trace("Send " + T.ToString());
        GetGame().RPCSingleParam(player, GetType(), params, guaranteed, recipient);
    }
}
