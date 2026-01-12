# Change: 更新 GitHub Actions Release 工作流以支持 RELEASE_NOTES.md

## Why
当前 GitHub Actions release 工作流使用硬编码的发布描述，无法自动从 RELEASE_NOTES.md 读取版本变更说明。这导致：
- 发布描述需要手动维护，容易遗漏或与 RELEASE_NOTES.md 不同步
- 每次发布都需要手动更新工作流文件中的描述内容
- 无法利用已有的 RELEASE_NOTES.md 模板和结构化内容

通过集成 RELEASE_NOTES.md，可以实现：
- 自动从文件读取发布说明
- 保持发布描述与文档的一致性
- 简化发布流程，减少手动操作

## What Changes
- **更新 `.github/workflows/release.yml`**:
  - 添加步骤读取 RELEASE_NOTES.md 文件内容
  - 处理模板占位符（{{VERSION}}, {{DATE}}, {{FIRMWARE_VERSION}}, {{RELEASE_URL}}）
  - 将处理后的内容作为 GitHub Release 的 body
  - 保留现有的固件构建和上传功能

- **文档更新**:
  - 在 README 或文档中添加 RELEASE_NOTES.md 使用说明
  - 说明如何填写和更新发布说明模板

## Impact
- **影响的规范**: CI/CD 自动化流程
- **影响的代码**: 
  - `.github/workflows/release.yml` - GitHub Actions 工作流
  - `RELEASE_NOTES.md` - 发布说明模板（使用方式说明）
- **无破坏性变更**: 此变更向后兼容，不影响现有发布流程
