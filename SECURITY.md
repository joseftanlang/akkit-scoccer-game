<!--
  SECURITY.md
  This file explains the project's security policy and how to report issues.
  The comment blocks (HTML comments) are intended for repository readers
  and maintainers to explain the purpose of each section; regular text
  is visible in rendered Markdown for end users.
-->

# Security Policy

<!-- Purpose: short summary for users scanning the file -->
This document explains how to report security issues and what to expect after reporting. Please use the channels below for responsible disclosure; do not create public issues for active vulnerabilities.

## Reporting a Vulnerability

<!-- Explain preferred contact method and what to include in a report -->
To report a security issue, please open a private issue (if your Git hosting supports private issues) or email the maintainer at the address listed in the repository metadata. If you cannot reach a private channel, open an issue and mark it as a security report, then immediately contact the maintainer to request it be made private.

Include the following information when reporting:

- A clear description of the vulnerability and impact.
- Step-by-step reproduction instructions, or a minimal proof-of-concept.
- The affected versions and components (e.g., `application/`, `boot/`, specific drivers).
- Any suggested mitigations or patches if you have them.

Do NOT include proof-of-concept exploit code in a public issue if it could cause active harm. Use a private channel for sensitive artifacts.

## Supported Versions

<!-- Readers should know which branches/tags are supported -->
We currently support the repository's `main` branch and the latest tagged release (if any). If you believe a vulnerability affects older unsupported versions, include that in your report; we will advise on mitigation.

## Response Process

<!-- Outline how the team will handle reports -->
1. Acknowledgement: We will acknowledge receipt within 72 hours.
2. Triage: We will assess severity and reproduction steps.
3. Fix: We will work to produce a fix or mitigation and coordinate disclosure.
4. Disclosure: We will coordinate a public disclosure timeline with the reporter.

If you don't receive a timely response, please follow up or use the project's issue tracker to escalate.

## Public Disclosure

<!-- Responsible disclosure expectations -->
We ask reporters to allow a reasonable period for fixes before public disclosure. If immediate disclosure is required (for legal reasons), notify us during the report.

## Security Best Practices for Contributors

<!-- Helpful tips for contributors who change code -->
- Validate external inputs carefully; even embedded games can be exposed via serial, USB, or network bridges.
- Keep third-party libraries and toolchains up-to-date.
- Avoid embedding secrets in source code. If secrets are required for manufacturing or CI, keep them in encrypted/separate stores.
- When adding new peripherals or drivers, consider access control and error handling to avoid unintended behaviors.

## Emergency Contact

<!-- If you have a security contact email, list it here. If not, instruct to use issue tracker -->
If you need an urgent response, open a private issue or contact the maintainers via the repository's issue tracker and mention "security" in the title.

<!-- End of SECURITY.md comments -->
