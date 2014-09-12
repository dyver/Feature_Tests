#include <++cpp11.h>

int main() {
    AutoTypeDeduction();
    RangeForStatement();
    RightAngleBrackets();
    ControlOfDefaults();
    MoveNotCopy();
    EnumClass();
    ConstExpr();
    DeclType();
    InitializerLists();
    PreventingNarrowing();
    DelegatingConstructors();
    InClassMemberInitializers();
    InheritedConstructors();
    StaticAssertions();
    LongLong();
    NullPtr();
    SuffixReturnTypeSyntax();
    TemplateAlias();
    VariadicTemplates();
    UniformInitialization();
    RValueReferences();
    GeneralizedUnions();
    GeneralizedPODs();
    RawStringLiterals();
    UserDefinedLiterals();
    Attributes();
    Lambdas();
    LocalTypes();
    NoExcept();
    Alignment();
    OverrideControl();
    C99features();
    // dynamic initialization and destruction with concurrency
    // Stroustrup haven't write this article.
    CopyingExceptions();
    ExternTemplates();
    InlineNamespace();
    ExplicitConversionOperators();
    AlgorithmsImprovements();
    ContainerImprovements();
    Array();
    ForwardList();
    UnorderedContainers();
    Tuple();
    // metaprogramming and type traits
    // Stroustrup haven't write this article.
    FunctionAndBind();
    UniquePtr();
    SharedPtr();
    // weak_ptr
    //   i don't understand them partially...
    // Garbage collection ABI
    //   it may be included ...
    Threads();
    MutualExclusion();
    Locks();
    // Conditional variables
    // Stroustrup haven't write this article.
    TimeUtilities();
    // Atomics
    // Stroustrup haven't write this article.
    FutureAndPromise();
    Async();
    // Abandoning a process
    // Stroustrup haven't write this article.
    RandomNumberGeneration();
    RegularExpressions();
    /*
    // Concepts
    // unfortunately, they no in standard
    template<typename T, typename U>
        requires std::Assignable<T, U>
        void copy(T, U);
    */
    // C++14
    BinaryLiterals();
    return 0;
}
