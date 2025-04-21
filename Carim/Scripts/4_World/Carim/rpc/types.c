#ifndef CarimRPCTypes
#define CarimRPCTypes

enum CarimRPCTypes {
    START = -44999
}

enum CarimRPCTypesAutorun : CarimRPCTypes {
    AUTORUN
}

enum CarimRPCTypesChat : CarimRPCTypesAutorun {
    SEND
}

enum CarimRPCTypesParty : CarimRPCTypesChat {
    POSITIONS,
    MARKERS,
    REGISTER
}

#endif
