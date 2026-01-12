# ci-cd Specification

## Purpose
定义 CI/CD 自动化流程的规范，包括 GitHub Actions 工作流的构建、测试和发布流程。确保发布流程自动化、一致性和可维护性。
## Requirements
### Requirement: 自动从 RELEASE_NOTES.md 生成发布描述
GitHub Actions release 工作流 SHALL 自动从 RELEASE_NOTES.md 文件读取内容并生成 GitHub Release 描述。

#### Scenario: 发布时自动读取发布说明
- **WHEN** 推送版本标签（v*）触发 release 工作流
- **THEN** 工作流读取 RELEASE_NOTES.md 文件内容
- **AND** 替换模板占位符为实际值（版本号、日期、固件版本、下载链接）
- **AND** 将处理后的内容设置为 GitHub Release 的 body

#### Scenario: 模板占位符替换
- **WHEN** RELEASE_NOTES.md 包含占位符 {{VERSION}}, {{DATE}}, {{FIRMWARE_VERSION}}, {{RELEASE_URL}}
- **THEN** 工作流将 {{VERSION}} 替换为实际标签名（如 v1.0.0）
- **AND** 将 {{DATE}} 替换为当前日期（YYYY-MM-DD 格式）
- **AND** 将 {{FIRMWARE_VERSION}} 替换为从标签提取的版本号
- **AND** 将 {{RELEASE_URL}} 替换为 GitHub Release 页面链接

### Requirement: RELEASE_NOTES.md 使用文档
项目 SHALL 提供 RELEASE_NOTES.md 文件的使用说明，指导维护者如何填写和更新发布说明。

#### Scenario: 维护者查看使用说明
- **WHEN** 维护者需要准备新版本发布
- **THEN** 可以在文档中找到 RELEASE_NOTES.md 的填写指南
- **AND** 了解各个章节的用途和格式要求
- **AND** 了解占位符的自动替换机制

