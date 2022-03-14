import { getUserLocale } from '../lib/'

describe('getUserLocale', () => {
  it('works', () => {
    if (process.platform === 'win32') {
      const locale = getUserLocale()
      expect(locale).not.toBeUndefined()
      expect(typeof locale).toBe('string')
      expect(locale).toMatch(/^[a-z]{2}-[A-Z]{2}$/)
    }
  })
})
