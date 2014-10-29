#pragma once

#include "abstractprojectgenerator.h"
#include "types.h"

namespace generator {

    /**
     * @brief The Profile struct
     */
    struct Profile
    {
        QStringList headers;
        QStringList sources;

        ProfileVariables variables;
    };

    /**
     * @brief The BasicCppProjectGenerator class
     */
    class BasicCppProjectGenerator final : public AbstractProjectGenerator
    {
    public:
        BasicCppProjectGenerator();
        BasicCppProjectGenerator(const db::SharedDatabase &globalDb,
                                  const db::SharedDatabase &projectDb,
                                  const QString &outputDirectory = "");

    private:
        void doWrite() const override;
        void doGenerate() override;
        void generateFiles(const entity::SharedScope &scope, const SharedVirtualDirectory &directory);
        void addProfile();

        SharedVirtualDirectory m_RootOutputDirectory;
        Profile m_ProfileData;
    };

} // namespace generator